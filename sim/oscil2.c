/*
  Space Elevator simulation
  Copyright (C) 2003-2004 Blaise Gassend <blaise at gassend dot com>
  
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gif_lib.h>

#define NUMPOINTS 200
#define TIMESTEP ((double) .5)
#define BREAKPOINT 198

#define WIDTH 600
#define HEIGHT 600

GLdouble c_Re = 6.36e6; // Earth radius
GLdouble c_Ge = 3.68e14; // Earth Gravity
GLdouble c_Slim = 130e9; // Carbon nanotube max resistance
GLdouble c_Vang = 7.3e-5; // Earth rotation
GLdouble c_Ecnt = 1e12; // Young's modulus
GLdouble c_Dcnt = 1300; // Density of carbon nanotubes;
GLdouble c_Clen = 91e6; // Cable length
GLdouble c_Fs = 2; // Factor of safety
GLdouble c_Mpay = 1.2e3; // Payload mass
GLdouble c_Fr_cnt = 10; // Friction coefficient for cnt //
GLdouble c_Vele = 200 / 3.6; // Elevator target speed

GLdouble c_Rgeo;

typedef struct
{
  GLdouble x;
  GLdouble y;
  GLdouble z;
} vector_t;

typedef struct 
{
  vector_t pos, v, f; // position, velocity, force
  unsigned char r, g, b, a; // color
  GLdouble m; // mass
  GLdouble k; // spring rigidity
  GLdouble frict; // friction coefficient
  GLdouble initlen; // initial length of segment
  GLdouble tension; // tension
  GLdouble crosssect; // cross section
} point_t;

int numpoints;
point_t *points;
point_t elevator;
GLdouble curtime;

GifFileType *GIFfile;

void closeGIF()
{
  printf("closeGIF\n");
  EGifCloseFile(GIFfile);
}

void initGIF()
{
  int i;
  ColorMapObject *GIFcmap;
//  char loopheader[15] = "NETSCAPE2.0";
//  const int GIFBPC = 6;
//  const int GIFColors = GIFBPC * GIFBPC * GIFBPC;
//  char ColorTable[6] = { 0, 51, 102, 153, 204, 255 };
  
  GIFcmap = MakeMapObject(256, NULL);
  GIFfile = EGifOpenFileName("oscilout.gif", 0);
  
  for (i = 0; i < 256; i++)
  {
    double r, g, b, f;
    f = (i - 1) / 254.0;
    
    if (i == 0)
    {
      r = g = b = 0;
    }
    else if (3 * f < 1)
    {
      r = 3 * f;
      g = 0;
      b = 1 - 3 * f;
    }
    else if (3 * f < 2)
    {
      r = 1;
      g = 3 * f - 1;
      b = 0;
    }
    else 
    {
      r = 1;
      g = 1;
      b = 3 * f - 2;
    }

    GIFcmap->Colors[i].Red = r * 255;
    GIFcmap->Colors[i].Green = g * 255;
    GIFcmap->Colors[i].Blue = b * 255;
//    GIFcmap->Colors[i].Red = ColorTable[i % GIFBPC];
//    GIFcmap->Colors[i].Green = ColorTable[(i / GIFBPC) % GIFBPC];
//    GIFcmap->Colors[i].Blue = ColorTable[(i / GIFBPC / GIFBPC) % GIFBPC]; 
  }
  
  EGifPutScreenDesc(GIFfile, WIDTH, HEIGHT, 128, 0, GIFcmap);

/*  loopheader[11] = 3;
  loopheader[12] = 1;
  loopheader[13] = 50;
  loopheader[14] = 0;
  EGifPutExtension(GIFfile, 255, 15, loopheader);*/
  
  atexit(closeGIF);
}

void saveGIF()
{
  int w, h, i;
  unsigned char img[WIDTH * HEIGHT];

  printf("saveGIF\n");
  
  glReadBuffer(GL_BACK_LEFT);
  glReadPixels(0, 0, WIDTH, HEIGHT, GL_ALPHA, GL_UNSIGNED_BYTE, img);
  
  EGifPutImageDesc(GIFfile, 0, 0, WIDTH, HEIGHT, 0, NULL);
  i = 0;
  for (h = 0; h < HEIGHT; h++)
    for (w = 0; w < WIDTH; w++)
    {
      int col = img[i++];
//      col += ((int) img[i++]) * 6 / 256;
//      col += (((int) img[i++]) * 6 / 256) * 6;
//      col += (((int) img[i++]) * 6 / 256) * 6 * 6;
      EGifPutPixel(GIFfile, col);
    }      
  printf("saveGIF - done\n");
}

void *smalloc(size_t s)
{
  void *p = malloc(s);
  if (p) return p;
  fprintf(stderr, "Can't malloc.\n");
  exit(1);
}

inline void vset(vector_t *v, GLdouble x, GLdouble y, GLdouble z)
{
  v->x = x;
  v->y = y;
  v->z = z;
}

inline void vaddto(vector_t *vd, vector_t *vs)
{
  vd->x += vs->x;
  vd->y += vs->y;
  vd->z += vs->z;
}

inline void vaddscaled(vector_t *vd, GLdouble s, vector_t *vs)
{
  vd->x += s * vs->x;
  vd->y += s * vs->y;
  vd->z += s * vs->z;
}

inline void vsubfrom(vector_t *vd, vector_t *vs)
{
  vd->x -= vs->x;
  vd->y -= vs->y;
  vd->z -= vs->z;
}

inline GLdouble vdot(vector_t *v1, vector_t *v2)
{
  return 
    v1->x * v2->x +
    v1->y * v2->y +
    v1->z * v2->z;
}   

inline vector_t vcross(vector_t *v1, vector_t *v2)
{
  vector_t vo;

  vo.x = v1->y * v2->z - v1->z * v2->y;
  vo.y = v1->z * v2->x - v1->x * v2->z;
  vo.z = v1->x * v2->y - v1->y * v2->x;

  return vo;
}
  
inline vector_t vscale(GLdouble s, vector_t *v)
{
  vector_t vd;
  vd.x = s*v->x;
  vd.y = s*v->y;
  vd.z = s*v->z;
  return vd;
}

inline vector_t vsub(vector_t *v1, vector_t *v2)
{
  vector_t v;
  v.x = v1->x - v2->x;
  v.y = v1->y - v2->y;
  v.z = v1->z - v2->z;
  return v;
}

inline GLdouble vnorm(vector_t *v)
{
  return sqrt(vdot(v, v));
}

inline GLdouble vdist(vector_t *v1, vector_t *v2)
{
  vector_t d = vsub(v1, v2);
  
  return vnorm(&d);
}

#define COL_EARTH 1
#define COL_GEO 86
#define COL_CLIMBER 171

void setcol(point_t *p, GLdouble f)
{
  // blue - red - yellow - white
  
  GLdouble r, g, b;
    
  if (p->k == 0)
  {
    r = g = b = 0;
  }
  else if (3 * f < 1)
  {
    r = 3 * f;
    g = 0;
    b = 1 - 3 * f;
  }
  else if (3 * f < 2)
  {
    r = 1;
    g = 3 * f - 1;
    b = 0;
  }
  else 
  {
    r = 1;
    g = 1;
    b = 3 * f - 2;
  }

  p->r = r * 255;
  p->g = g * 255;
  p->b = b * 255;
  p->a = f * 254 + 1;
}

void init()
{
  int i;
  double tension = c_Mpay;
  double fcoef = 0;
  double mt = 0;
    
  curtime = -3600 * 0;
  numpoints = NUMPOINTS;
  points = smalloc((numpoints + 1) * sizeof(point_t)); // FIXME 
  
  for (i = 0; i < numpoints; i++)
  {
    vset(&points[i].pos, c_Clen * i / NUMPOINTS + c_Re, 0, 0);
    vset(&points[i].v, 0, 0, 0);
   
    points[i].crosssect = c_Fs * tension / c_Slim;
    points[i].k = c_Ecnt / (c_Clen / NUMPOINTS) * points[i].crosssect;
    points[i].initlen = (c_Clen / NUMPOINTS - tension / points[i].k);
    points[i].frict = c_Fr_cnt;
    mt += points[i].m = points[i].initlen * points[i].crosssect * c_Dcnt;
    
    fcoef = c_Ge / (points[i].pos.x * points[i].pos.x) - points[i].pos.x * c_Vang * c_Vang;
//    if (i < 10)  
      printf("c: %e t: %e fc: %e r: %e il: %e k: %e m: %e\n", points[i].crosssect, tension, fcoef, points[i].pos.x, points[i].initlen, points[i].k, points[i].m);
    tension += fcoef * points[i].m;
  }

  points[numpoints - 1].m = -tension / fcoef * 1; // FIXME

  printf("mc: %e mt: %e\n", points[numpoints - 1].m, mt);

  vset(&elevator.pos, c_Re + 500000000, 0, 0);
  vset(&elevator.v, 0, 0, 0);
  elevator.m = c_Mpay;
}

GLdouble maxforce, curforce;
  
inline void pointdynamics(point_t *curpt)
{
  GLdouble r = vnorm(&curpt->pos);
  vector_t grav;
  vector_t rotf;
  vector_t coriolis;

  if (r > c_Re)
  {
    grav = vscale(-c_Ge * curpt->m / pow(r,3), &curpt->pos);
    vaddto(&curpt->f, &grav);
  }
  else
  { // Keep stuff out of the Earth
    vector_t scaled;
    curpt->pos = vscale(c_Re / vnorm(&curpt->pos), &curpt->pos);
    scaled = vscale(-vdot(&curpt->pos, &curpt->v) / c_Re / c_Re, &curpt->pos);
    vaddto(&curpt->v, &scaled);
    curpt->v = vscale(0, &curpt->v);
  }

  rotf = vscale(c_Vang * c_Vang * curpt->m, &curpt->pos);
  rotf.z = 0;
  vset(&coriolis, 2 * curpt->v.y * curpt->m * c_Vang, -2 * curpt->v.x * curpt->m * c_Vang, 0);
  vaddto(&curpt->f, &rotf);
  vaddto(&curpt->f, &coriolis);

  //    if (i == 1)  
  //      printf("d: %e t: %e f: %e m: %e g: %e r: %e\n", points[i+1].pos.x - curpt->pos.x, 
  //	  curpt->tension, curpt->f.x, curpt->m, grav.x, r);

  if (curtime > 0)
  {
    vaddscaled(&curpt->v, TIMESTEP / curpt->m, &curpt->f); 
    vaddscaled(&curpt->pos, TIMESTEP, &curpt->v);
  }
  else
  {
    //vaddscaled(&curpt->pos, TIMESTEP / curpt->m * 100, &curpt->f);
    vaddscaled(&curpt->v, TIMESTEP / curpt->m, &curpt->f); 
    vaddscaled(&curpt->pos, TIMESTEP, &curpt->v);
    curpt->v = vscale(.99, &curpt->v);
  }
}

void simul()
{
  int i, elevatorpos;
//  double gfact = 1;
//  double afact = 1;

//  if (curtime < 20)
//  {
//    afact = curtime / 20;
//    gfact = 0;
//  }
//  else if (curtime < 40)
//  {
//    gfact = curtime / 20 - 1;
//  }
  
  // Clear forces.
  vset(&elevator.f, 0, 0, 0);
  
  for (i = 0; i < numpoints; i++)
    vset(&points[i].f, 0, 0, 0);
  
  elevatorpos = numpoints;
//  for (elevatorpos = 1; elevatorpos < numpoints; elevatorpos++)
//    if (elevator.pos.x <= points[elevatorpos].pos.x)
//      break;

  if (elevatorpos < numpoints)
  {
    vector_t elev_relv;
    vector_t elev_targv;
    vector_t elev_f;

    vector_t cable_elem = vsub(&points[elevatorpos].pos, &points[elevatorpos - 1].pos);
    cable_elem = vscale(1 / vnorm(&cable_elem), &cable_elem);
    elev_targv = vscale(c_Vele, &cable_elem);
    elev_relv = vsub(&elevator.v, &points[elevatorpos].v);
    elev_f = vsub(&elev_targv, &elev_relv);
    elev_f = vscale(250, &elev_f); // FIXME set scale sanely
    vaddto(&elevator.f, &elev_f);
    vsubfrom(&points[i].f, &elev_f);
    // End of velocity tracking.
    
    elev_f = vsub(&elevator.pos, &points[elevatorpos].pos);
    vaddscaled(&elev_f, -vdot(&elev_f, &cable_elem), &cable_elem); 
    elev_f = vscale(-.01, &elev_f); // FIXME set scale sanely
    vaddto(&elevator.f, &elev_f);
    vsubfrom(&points[i].f, &elev_f);
    // End of lateral position tracking.
    
//    printf("t: %5f x: %5e vx: %5e dvx: %5e ", curtime / 3600, elevator.pos.x, elevator.v.x, elev_relv.x);
  }

//  printf("n:%4i\n", elevatorpos);
  
  for (i = 0; i < numpoints - 1; i++)
  {
    vector_t vdiff;
    GLdouble axialv, frict, elast;
    
    vector_t diff = vsub(&points[i+1].pos, &points[i].pos);
    GLdouble l = vnorm(&diff);
    vector_t f;
    elast = points[i].k * (1 - points[i].initlen / l);
    if (elast < 0) elast = 0;
    points[i].tension = elast * l;

/*    if (elast / points[i].crosssect > c_Slim)
    {
      printf("break %i\n", i);
      points[i].k = 0;
      points[i].frict = 0;
    }*/
    
    vdiff = vsub(&points[i+1].v, &points[i].v);
    axialv = vdot(&vdiff, &diff) / l;
    frict = axialv / l * points[i].frict;
   
    f = vscale(elast + frict, &diff);
    vaddto(&points[i].f, &f);
    vsubfrom(&points[i+1].f, &f);
  }         

//  maxforce = 0;
//  for (i = 0; i < numpoints; i++)
//  {
//    curforce = points[i].tension;
//    if (curforce > maxforce)
//      maxforce = curforce;
//  }

//  if (maxforce == 0)
//    maxforce = 1; // Any scale will do.
  
  for (i = 0; i < numpoints; i++)
  {
    double loading = points[i].tension / points[i].crosssect / c_Slim;
    //    setcol(&points[i], fabs(points[i].v.x/ (100/3.6))); 
    setcol(&points[i], loading);
    if (loading > 1 && curtime > 0)
    {
      points[i].k = 0;
      points[i].frict = 0;
    }
  }

  for (i = 0; i < numpoints; i++)
    pointdynamics(&points[i]);

  pointdynamics(&elevator);
    
//  if (curtime < 10)
  { // *****************
    // Boundary cond at anchor.
    // ***********************
    //points[0].pos.x = c_Re;// + 10000 * sin(pow(curtime,1.1) / 1000);// + (curtime < 10000  || curtime > 10100 ? 0 : 1000000);
    points[0].pos.z = c_Re * sin(0 / 180.0 * M_PI);
    points[0].pos.x = c_Re * cos(0 / 180.0 * M_PI);
//    points[0].pos.z = 0;
    points[0].pos.y = 0;
//    vset(&points[0].pos, c_Re, 0, 0);
    vset(&points[0].v, 0, 0, 0);
    
// ########    points[0].f.x = 

// Break here
    if (curtime > 1)
    {
      points[BREAKPOINT].k = 0;   
      points[BREAKPOINT].frict = 0;   
    }
  }

    //  if (curtime < .02)
//    vset(&points[0].pos, .05 * cos(curtime), .05 * sin(curtime), 0);
//    vset(&points[0].v, -.05 * (sin(curtime) - 1), .05 * cos(curtime), 0);
//  else
//    vset(&points[0].pos, -.75, 0, 0);
//  vset(&points[numpoints - 1].pos, .75, 0, 0);

//    printf("\n");
    
    curtime += TIMESTEP;
    
//  printf("%e %e\n", points[numpoints - 1].pos.x, points[numpoints - 1].pos.y);
}

void mainloop()
{
  int i;

//  sleep(1);
  
  printf("%f\n", curtime / 3600);
//  printf("%f %f %f\n", curtime, vnorm(&points[numpoints-1].pos), maxforce);

  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glClear( GL_COLOR_BUFFER_BIT );
  glMatrixMode(GL_MODELVIEW);

  glColor4ub(0,0,255,COL_EARTH);
  glutWireSphere(c_Re,20,10);
  glColor4ub(255,0,0,COL_GEO);
  glutWireSphere(c_Rgeo,20,10);
  
  glBegin(GL_LINE_STRIP);
  for (i = 0; i < numpoints; i++)
  {
    if (i > 0 && points[i - 1].k == 0)
    {
      glEnd();
      glBegin(GL_LINE_STRIP);
    }
    
    glColor4ub(points[i].r, points[i].g, points[i].b, points[i].a);
    glVertex3d(points[i].pos.x, points[i].pos.y, points[i].pos.z);
  }
  glEnd();

  glBegin(GL_POINTS);
  glColor4ub(0,255,0,COL_CLIMBER);
  glVertex3d(elevator.pos.x, elevator.pos.y, elevator.pos.z);
  glEnd();

/*  glMatrixMode(GL_MODELVIEW);
  glColor4ub(255,255,255,COL_CLIMBER);
  glDisable (GL_DEPTH_TEST);
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(-1100,0,0);
  glLineWidth(4.0);
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'A');
  glLineWidth(1.0);
  glPopMatrix();*/

  //  glDrawArrays(GL_LINE_STRIP, 0, numpoints);
  
  glutSwapBuffers();
  saveGIF();
  
  for (i = 0; i < 600; i++)
    simul();

}

int mousex;
int mousey;
int mousebutton;

void motion(int x, int y)
{
  int dx = x - mousex;
  int dy = y - mousey;
    
  mousex = x;
  mousey = y; 
  
  glMatrixMode(GL_MODELVIEW);
  
  if (mousebutton == GLUT_LEFT_BUTTON)
  {
    GLdouble m[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, m);
    glLoadIdentity();
    dx = 0; // FIXME
    glRotated(sqrt(dx*dx + dy*dy), dy, dx, 0);
    glMultMatrixd(m);
  }
  else if (mousebutton == GLUT_RIGHT_BUTTON)
  {
    GLdouble m[16];
    GLdouble a = exp(dy / 100.0);

    dx = 0; // FIXME
    glGetDoublev(GL_MODELVIEW_MATRIX, m);
    glLoadIdentity();
    glRotated(dx, 0, 0, 1);
    glMultMatrixd(m);
    
    glScaled(a,a,a);
  }
  
  glutPostRedisplay();
}

void mousebuttonevent(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN)
  {
    mousex = x;
    mousey = y;
    mousebutton = button;
  }
}

int main(int argc, char **argv)
{
  c_Rgeo = pow(c_Ge / c_Vang / c_Vang, 1./3.);
  
  initGIF();
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA);
//  glutInitWindowPosition(100,100)

  glutInitWindowSize(WIDTH,HEIGHT);
  glutCreateWindow("Elevator");
  glutDisplayFunc(mainloop);
  glutIdleFunc(mainloop);
  glutMouseFunc(mousebuttonevent);
  glutMotionFunc(motion);
  
  glMatrixMode(GL_MODELVIEW);
  glScaled(1/90e6,1/90e6,1/90e6);

  init();
  
//  glEnableClientState(GL_VERTEX_ARRAY);
//  glVertexPointer(numpoints, GL_DOUBLE, sizeof(point_t), 
//	&points[0].pos.x);

  glutMainLoop();
  return 0;
}
