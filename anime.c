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
static int r = 0; //��]�p�̐ݒ�
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�f�v�X�o�b�t�@�̃N���A
glLoadIdentity();
/* ���_�ʒu�Ǝ������� */
gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
/* �����̈ʒu�ݒ� */
glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
glPushMatrix();
glTranslatef(ox,oy,oz);
glRotatef(r, 0.5, -0.5, -0.5); //��]�F���̂悤�ɁA�����̎��𒆐S�ɉ�]�����邱�Ƃ��ł��܂��B
/* �}�`�̐F (gold) */
glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_diffuse);
glMaterialfv(GL_FRONT, GL_AMBIENT, gold_ambient);
glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_specular);
glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, gold_shininess);
/* �}�`�̕`�� */
glutSolidTeapot(0.8);
if (glutLayerGet(GLUT_NORMAL_DAMAGED) == 0)//��ʂ��`��������ꂽ��
{
if (r++ >= 360) //�p�xrx��1���₵���l�i++r�j��360�ȏ�ɂȂ�����
{
r = 0; //�p�x��0�ɖ߂�
glutIdleFunc(0); //�A�j���[�V�������Ƃ߂�
}
}
oy=oy-0.02;
glPopMatrix();
glutPostRedisplay(); //�ĕ`��C�x���g�𔭐�
glutSwapBuffers();
}
void resize(int w, int h)
{
glViewport(0, 0, w, wh = h);
/* �����ϊ��s��̐ݒ� */
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
/* ���f���r���[�ϊ��s��̐ݒ� */
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
glLightfv(GL_LIGHT0,GL_DIFFUSE,white); /* �������� */
glLightfv(GL_LIGHT1,GL_DIFFUSE,white);
glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);/* ���ʔ��ˏ��������A���� */
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
  /* ESC �� q ���^�C�v������I�� */
  if (key == '\033' || key == 'q') {
    exit(0);
  }
}

int main(int argc, char *argv[])
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
glutInitWindowSize(1000, 1000);
glutCreateWindow("�A�j���[�V����");
glutDisplayFunc(display);
glutReshapeFunc(resize);
glutKeyboardFunc(keyboard);
glutMouseFunc(mouse);
init();
glutMainLoop();
return 0;
}