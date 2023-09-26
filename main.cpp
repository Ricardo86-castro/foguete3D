/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

GLfloat angle, fAspect;

GLfloat rotateX = 0.0f;
GLfloat rotateY = 0.0f;


void foguete(float raio, float altura, int n){
    int i;
    float angle = 2.0f * M_PI / n;

    float top_x = 0.0f, top_y = altura / 2.0f, top_z = 0.0f;
    float bottom_x = 0.0f, bottom_y = - altura / 2.0f, bottom_z = 0.0f;

    // cilindro corpo do foguete
    glBegin(GL_TRIANGLES);
    for(i = 0; i < n; i++){
            float p0_x = raio * cos(i * angle);
            float p0_y = 0.0f;
            float p0_z = raio * sin(i * angle);

            float p1_x = raio * cos((i + 1) * angle);
            float p1_y = 0.0f;
            float p1_z = raio * sin((i + 1) * angle);

            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(top_x, top_y, top_z);
            glVertex3f(p0_x, top_y, p0_z);
            glVertex3f(p1_x, top_y, p1_z);

            glNormal3f(p0_x / raio, 0.0f, p0_z / raio);
            glVertex3f(p0_x, top_y, p0_z);
            glNormal3f(p0_x / raio, 0.0f, p0_z / raio);
            glVertex3f(p0_x, bottom_y, p0_z);
            glNormal3f(p1_x / raio, 0.0f, p1_z / raio);
            glVertex3f(p1_x, top_y, p1_z);

            glNormal3f(p1_x / raio, 0.0f, p1_z / raio);
            glVertex3f(p1_x, top_y, p1_z);
            glNormal3f(p0_x / raio, 0.0f, p0_z / raio);
            glVertex3f(p0_x, bottom_y, p0_z);
            glNormal3f(p1_x / raio, 0.0f, p1_z / raio);
            glVertex3f(p1_x, bottom_y, p1_z);

            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(p0_x, bottom_y, p0_z);
            glVertex3f(p1_x, bottom_y, p1_z);
            glVertex3f(bottom_x, bottom_y, bottom_z);

    }
    glEnd();


     // Desenho do fundo do foguete (disco)
    glColor3f(0.5f, 0.5f, 0.5f); // Cor do fundo do foguete (cinza)
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, -20.0f, 0.0f);  // Centro do disco
    int numSegments = 100;
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * M_PI * i / numSegments;
        float x = 15.0f * cos(theta);
        float z = 15.0f * sin(theta);
        glVertex3f(x, -40.0f, z);
    }
    glEnd();

    glColor3f(0.8f, 0.3f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, -60.0f, 0.0f);
    int numSegm = 100;
    for(int i = 0; i <= numSegm; i++){
        float theta = 2.0f * M_PI * i / numSegm;
        float x = 14.0f * cos(theta);
        float z = 14.0f * sin(theta);
        glVertex3f(x, -40.0f, z);
    }
    glEnd();


    // Desenho da esfera no topo do cilindro
    glColor3f(0.5f, 0.5f, 0.5f); // Cor da esfera (cinza)
    glPushMatrix();
    glTranslatef(0.0f, 10.0f, -10.0f);  // Posiciona a esfera no topo do cilindro
    glutSolidSphere(10.0f, 50, 50);  // Desenha a esfera
    glPopMatrix();

    // Desenho da esfera no topo do cilindro
    glColor3f(0.5f, 0.5f, 0.5f); // Cor da esfera (cinza)
    glPushMatrix();
    glTranslatef(0.0f, 10.0f, 10.0f);  // Posiciona a esfera no topo do cilindro
    glutSolidSphere(10.0f, 50, 50);  // Desenha a esfera
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 30.0f, 0.0f);  // Posiciona o cone acima do cilindro
    glColor3f(1.0f, 0.0f, 0.0f);       // Define a cor do cone (vermelho)

    // Código para desenhar o cone
    int numSlices = 50;
    float coneHeight = 30.0f;
    float coneRadius = 15.0f;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < numSlices; i++) {
        float angle0 = 2.0f * M_PI * i / numSlices;
        float angle1 = 2.0f * M_PI * (i + 1) / numSlices;

        float x0 = coneRadius * cos(angle0);
        float z0 = coneRadius * sin(angle0);
        float x1 = coneRadius * cos(angle1);
        float z1 = coneRadius * sin(angle1);

        glVertex3f(0.0f, coneHeight, 0.0f);  // Vertex at the tip of the cone
        glVertex3f(x0, 0.0f, z0);            // Vertex at the base of the cone (slice i)
        glVertex3f(x1, 0.0f, z1);            // Vertex at the base of the cone (slice i + 1)
    }
    glEnd();

    glPopMatrix();

    // Desenho das laterais do foguete
    glColor3f(0.5f, 0.5f, 0.5f);  // Cor das laterais (cinza)

    // Lado esquerdo
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 0.0f, 0.0f);   // Vértice inferior esquerdo
    glVertex3f(-30.0f, -30.0f, 0.0f);  // Vértice superior
    glVertex3f(0.0f, -30.0f, .0f);    // Vértice superior direito
    glEnd();

    // Lado direito
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 0.0f, 0.0f);     // Vértice inferior esquerdo
    glVertex3f(0.0f, -30.0f, 0.0f);    // Vértice superior
    glVertex3f(30.0f, -30.0f, 0.0f);   // Vértice superior direito
    glEnd();


}



// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);


    // Desenho de um cilindro
    foguete(15.0f, 60.0f, 100);


    // Executa os comandos OpenGL
    glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    angle=0;

    //habilita fonte de luz e iluminacao
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);

    //ajustando a cor do objeto - material
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();
   // fAspect=0.5;
    // Especifica a projeção perspectiva
    gluPerspective(45,fAspect,0.1,500);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Especifica posição do observador e do alvo
    //x,y,z do observador
    //x,y,z do centro visao
    //x,y,z matriz up
    gluLookAt(0,80,200, 0,0,0, 0,1,0);
}

void defineIlumination(){
    // Define os parâmetros através de vetores RGBA - o último valor deve ser
    // sempre 1.0f (transparência, não usada neste exemplo)
    float luzAmbiente[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float luzDifusa[] = {0.7f, 0.7f, 0.7f, 1.0f};
    float luzEspecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    //x,y,z, w
    float posicaoLuz[] = {0.0f, 50.0f, 0.0f, 1.0f};
    float spotLuz[] = {0.0f, -1.0f, 0.0f};



    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    /*
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotLuz);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 20);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30);
    */
    /*
    glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);
    */




    // Brilho do material
    float especularidade[] = {1.0f, 1.0f, 1.0f, 1.0f};
    int especMaterial = 60;

    // Define a reflectância do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);

    // Define a concentração do brilho
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);

    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    defineIlumination();

    EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar os eventos do teclado:
void Teclado(unsigned char key, int x, int y) {
    switch(key) {
        case 'x':
            rotateX += 5.0f;
            break;
        case 'X':
            rotateX -= 5.0f;
            break;
        case 'y':
            rotateY += 5.0f;
            break;
        case 'Y':
            rotateY -= 5.0f;
            break;
    }

    glutPostRedisplay();
}



// Programa Principal
int main(int argc,char *argv[]){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutCreateWindow("Visualizacao 3D");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(Teclado);
    glEnable(GL_DEPTH_TEST);
    //glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    Inicializa();
    glutMainLoop();
}
