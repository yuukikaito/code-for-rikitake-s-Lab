#include <glut.h>

double y=0;
GLdouble ox,oy,oz;
int wh;

GLfloat light0pos[] = { 3.0, 4.0, 4.0, 1.0 };
GLfloat light1pos[] = { 5.0, 3.0, 0.0, 1.0 };
GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
GLfloat gold_ambient[] = {0.24725, 0.1995, 0.0745, 1.0},
gold_diffuse[] = {0.75164, 0.60648, 0.22648, 1.0},
gold_specular[] = {0.628281, 0.555802, 0.366065, 1.0},
gold_shininess[]= {51.2};
void display(void)
{
static int r = 0; //回転角の設定
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //デプスバッファのクリア
glLoadIdentity();
/* 視点位置と視線方向 */
gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
/* 光源の位置設定 */
glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
glPushMatrix();
glTranslatef(ox,oy,oz);
glRotatef(r, 0.5, -0.5, -0.5); //回転：このように、複数の軸を中心に回転させることもできます。
/* 図形の色 (gold) */
glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_diffuse);
glMaterialfv(GL_FRONT, GL_AMBIENT, gold_ambient);
glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_specular);
glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, gold_shininess);
/* 図形の描画 */
glutSolidTeapot(0.8);
if (glutLayerGet(GLUT_NORMAL_DAMAGED) == 0)//画面が描き換えられたら
{
if (r++ >= 360) //角度rxを1増やした値（++r）が360以上になったら
{
r = 0; //角度を0に戻す
glutIdleFunc(0); //アニメーションをとめる
}
}
oy=oy-0.02;
glPopMatrix();
glutPostRedisplay(); //再描画イベントを発生
glutSwapBuffers();
}
void resize(int w, int h)
{
glViewport(0, 0, w, wh = h);
/* 透視変換行列の設定 */
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
/* モデルビュー変換行列の設定 */
glMatrixMode(GL_MODELVIEW);
}
void init(void)
{
glClearColor(0.0, 0.0, 0.0, 1.0);
glEnable(GL_DEPTH_TEST);
glEnable(GL_AUTO_NORMAL);
glEnable(GL_NORMALIZE);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_LIGHT1);
glLightfv(GL_LIGHT0,GL_DIFFUSE,white); /* 白い光源 */
glLightfv(GL_LIGHT1,GL_DIFFUSE,white);
glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);/* 鏡面反射処理をリアルに */
}

static void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		GLdouble model[16],proj[16];
		GLint view[4];
		GLfloat z;

		glGetDoublev(GL_MODELVIEW_MATRIX, model);
		glGetDoublev(GL_PROJECTION_MATRIX,proj);
		glGetIntegerv(GL_VIEWPORT,view);

		glReadPixels(x,wh-y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&z);
		gluUnProject(x,wh-y,z,model,proj,view,&ox,&oy,&oz);
	}
 printf(" at (%d, %d, %d)\n", ox, oy,oz);
}

static void keyboard(unsigned char key, int x, int y)
{
  /* ESC か q をタイプしたら終了 */
  if (key == '\033' || key == 'q') {
    exit(0);
  }
}

int main(int argc, char *argv[])
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
glutInitWindowSize(1000, 1000);
glutCreateWindow("アニメーション");
glutDisplayFunc(display);
glutReshapeFunc(resize);
glutKeyboardFunc(keyboard);
glutMouseFunc(mouse);
init();
glutMainLoop();
return 0;
}