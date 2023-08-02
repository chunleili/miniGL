#include <Eigen/Dense>
#include <iostream>

#include "Common/Common.h"
#include "Visualization/MiniGL.h"


using namespace PBD;
using namespace std;

void timeStep ();
void render ();
void cleanup();
void reset();
void selection(const Vector2i &start, const Vector2i &end, void *clientData);
void createSphereBuffers(Real radius, int resolution);
void renderSphere(const Vector3r &x, const float color[]);
void releaseSphereBuffers();


const Real particleRadius = static_cast<Real>(0.025);

bool doPause = true;
Vector3r oldMousePos;
GLuint elementbuffer;
GLuint normalbuffer;
GLuint vertexbuffer;
int vertexBufferSize = 0;
GLint context_major_version, context_minor_version;
Shader m_shader;
Shader m_shaderFlat;
Shader m_shaderTex;

Shader& getShader() { return m_shader; }
Shader& getShaderTex() { return m_shaderTex; }
Shader& getShaderFlat() { return m_shaderFlat; }
void shaderTexBegin(const float *col);
void shaderTexEnd();
void shaderBegin(const float *col);
void shaderEnd();
void shaderFlatBegin(const float* col);
void shaderFlatEnd();



// main 
int main( int argc, char **argv )
{

	MiniGL::init(argc, argv, 1280, 1024, "demo", false, false);
	MiniGL::initLights();
	MiniGL::initTexture();
	MiniGL::getOpenGLVersion(context_major_version, context_major_version);
	MiniGL::setViewport(40.0, 0.1f, 500.0, Vector3r(0.0, 3.0, 8.0), Vector3r(0.0, 0.0, 0.0));


	MiniGL::setClientIdleFunc(timeStep);
	MiniGL::addKeyFunc('r', reset);
	MiniGL::setClientSceneFunc(render);
	MiniGL::setViewport (40.0, 0.1f, 500.0, Vector3r (0.0, 3.0, 8.0), Vector3r (0.0, 0.0, 0.0));

	MiniGL::getOpenGLVersion(context_major_version, context_minor_version);
	if (context_major_version >= 3)
		createSphereBuffers((Real)particleRadius, 8);

	MiniGL::mainLoop();	

	return 0;
}


void shaderTexBegin(const float *col)
{
	m_shaderTex.begin();
	glUniform1f(m_shaderTex.getUniform("shininess"), 5.0f);
	glUniform1f(m_shaderTex.getUniform("specular_factor"), 0.2f);

	GLfloat matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glUniformMatrix4fv(m_shaderTex.getUniform("modelview_matrix"), 1, GL_FALSE, matrix);
	GLfloat pmatrix[16];
	glGetFloatv(GL_PROJECTION_MATRIX, pmatrix);
	glUniformMatrix4fv(m_shaderTex.getUniform("projection_matrix"), 1, GL_FALSE, pmatrix);
	glUniform3fv(m_shaderTex.getUniform("surface_color"), 1, col);
}

void shaderTexEnd()
{
	m_shaderTex.end();
}

void shaderBegin(const float *col)
{
	m_shader.begin();
	glUniform1f(m_shader.getUniform("shininess"), 5.0f);
	glUniform1f(m_shader.getUniform("specular_factor"), 0.2f);

	GLfloat matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glUniformMatrix4fv(m_shader.getUniform("modelview_matrix"), 1, GL_FALSE, matrix);
	GLfloat pmatrix[16];
	glGetFloatv(GL_PROJECTION_MATRIX, pmatrix);
	glUniformMatrix4fv(m_shader.getUniform("projection_matrix"), 1, GL_FALSE, pmatrix);
	glUniform3fv(m_shader.getUniform("surface_color"), 1, col);
}

void shaderEnd()
{
	m_shader.end();
}

void shaderFlatBegin(const float* col)
{
	m_shaderFlat.begin();
	glUniform1f(m_shaderFlat.getUniform("shininess"), 5.0f);
	glUniform1f(m_shaderFlat.getUniform("specular_factor"), 0.2f);

	GLfloat matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glUniformMatrix4fv(m_shaderFlat.getUniform("modelview_matrix"), 1, GL_FALSE, matrix);
	GLfloat pmatrix[16];
	glGetFloatv(GL_PROJECTION_MATRIX, pmatrix);
	glUniformMatrix4fv(m_shaderFlat.getUniform("projection_matrix"), 1, GL_FALSE, pmatrix);
	glUniform3fv(m_shaderFlat.getUniform("surface_color"), 1, col);
}

void shaderFlatEnd()
{
	m_shaderFlat.end();
}

void reset()
{}


void timeStep ()
{
	unsigned update_per_render =  1;
	for (unsigned int i = 0; i < update_per_render; i++)
	{}
}


void render ()
{
	// Draw simulation model
	std::vector<Vector3r> particlePos = {{0,0,0},{0,0,1},{0,1,0},{1,0,0},{0.5,0.5,0.5}};
	const unsigned int nParticles = particlePos.size();

	float surfaceColor[4] = { 0.2f, 0.6f, 0.8f, 1 };
	float speccolor[4] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, surfaceColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, surfaceColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, speccolor);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);
	glColor3fv(surfaceColor);

	glPointSize(4.0);

	for (unsigned int i = 0; i < nParticles; i++)
	{
		float fluidColor[4] = { 0.2f, 0.2f, 0.2f, 1.0 };
		MiniGL::hsvToRgb(0.55f, 1.0f, 0.5f + 0.0, fluidColor);
		renderSphere(particlePos[i], fluidColor);
	}


	float gridColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	MiniGL::drawGrid_xz(gridColor);
	
	MiniGL::coordinateSystem();

}



void createSphereBuffers(Real radius, int resolution)
{
	// Real PI = static_cast<Real>(M_PI);
	Real PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;
	// vectors to hold our data
	// vertice positions
	std::vector<Vector3r> v;
	// normals
	std::vector<Vector3r> n;
	std::vector<unsigned short> indices;

	// initiate the variable we are going to use
	Real X1, Y1, X2, Y2, Z1, Z2;
	Real inc1, inc2, inc3, inc4, radius1, radius2;

	for (int w = 0; w < resolution; w++)
	{
		for (int h = (-resolution / 2); h < (resolution / 2); h++)
		{
			inc1 = (w / (Real)resolution) * 2 * PI;
			inc2 = ((w + 1) / (Real)resolution) * 2 * PI;
			inc3 = (h / (Real)resolution)*PI;
			inc4 = ((h + 1) / (Real)resolution)*PI;

			X1 = sin(inc1);
			Y1 = cos(inc1);
			X2 = sin(inc2);
			Y2 = cos(inc2);

			// store the upper and lower radius, remember everything is going to be drawn as triangles
			radius1 = radius*cos(inc3);
			radius2 = radius*cos(inc4);

			Z1 = radius*sin(inc3);
			Z2 = radius*sin(inc4);

			// insert the triangle coordinates
			v.push_back(Vector3r(radius1*X1, Z1, radius1*Y1));
			v.push_back(Vector3r(radius1*X2, Z1, radius1*Y2));
			v.push_back(Vector3r(radius2*X2, Z2, radius2*Y2));

			indices.push_back((unsigned short)v.size() - 3);
			indices.push_back((unsigned short)v.size() - 2);
			indices.push_back((unsigned short)v.size() - 1);

			v.push_back(Vector3r(radius1*X1, Z1, radius1*Y1));
			v.push_back(Vector3r(radius2*X2, Z2, radius2*Y2));
			v.push_back(Vector3r(radius2*X1, Z2, radius2*Y1));

			indices.push_back((unsigned short)v.size() - 3);
			indices.push_back((unsigned short)v.size() - 2);
			indices.push_back((unsigned short)v.size() - 1);

			// insert the normal data
			n.push_back(Vector3r(X1, Z1, Y1));
			n.push_back(Vector3r(X2, Z1, Y2));
			n.push_back(Vector3r(X2, Z2, Y2));
			n.push_back(Vector3r(X1, Z1, Y1));
			n.push_back(Vector3r(X2, Z2, Y2));
			n.push_back(Vector3r(X1, Z2, Y1));
		}
	}

	for (unsigned int i = 0; i < n.size(); i++)
		n[i].normalize();


	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(Vector3r), &v[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, n.size() * sizeof(Vector3r), &n[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Generate a buffer for the indices as well
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// store the number of indices for later use
	vertexBufferSize = (unsigned int)indices.size();

	// clean up after us
	indices.clear();
	n.clear();
	v.clear();
}

void renderSphere(const Vector3r &x, const float color[])
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);


	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexPointer(3, GL_REAL, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glNormalPointer(GL_REAL, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	glPushMatrix();
	glTranslated(x[0], x[1], x[2]);
	glDrawElements(GL_TRIANGLES, (GLsizei)vertexBufferSize, GL_UNSIGNED_SHORT, 0);
	glPopMatrix();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void releaseSphereBuffers()
{
	if (elementbuffer != 0)
	{
		glDeleteBuffers(1, &elementbuffer);
		elementbuffer = 0;
	}
	if (normalbuffer != 0)
	{
		glDeleteBuffers(1, &normalbuffer);
		normalbuffer = 0;
	}
	if (vertexbuffer != 0)
	{
		glDeleteBuffers(1, &vertexbuffer);
		vertexbuffer = 0;
	}
}
