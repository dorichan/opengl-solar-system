/*	AUTHOR Dori Chan
	============================
	CONTROLS
	============================
	RIGHT MOUSE CLICK = menu
	UP ARROW = move obj
	q/Q = toggle obj
	l/L = toggle lights
	t/T = toggle textures
	F1 = cinematic camera
	F2 = stop camera
	F3 = zoom in
	F4 = zoom out
	F5 = default camera position
	============================
*/

#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <GL\glut.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include "globals.h"
#include "SOIL.h"
#include "glm.h"

GLMmodel* station = NULL;

int LoadGLTextures()
{
	texture[0] = SOIL_load_OGL_texture("planets/universe.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	texture[1] = SOIL_load_OGL_texture("planets/sun.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	texture[2] = SOIL_load_OGL_texture("planets/mercury.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	texture[3] = SOIL_load_OGL_texture("planets/venus.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	texture[4] = SOIL_load_OGL_texture("planets/earth.png", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	texture[5] = SOIL_load_OGL_texture("planets/mars.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	texture[6] = SOIL_load_OGL_texture("planets/jupiter.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	texture[7] = SOIL_load_OGL_texture("planets/saturn.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	texture[8] = SOIL_load_OGL_texture("planets/uranus.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	texture[9] = SOIL_load_OGL_texture("planets/neptune.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	texture[10] = SOIL_load_OGL_texture("planets/moon.jpg", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	return TRUE;
}

void drawmodel(void)
{
	if(!station)
	{
		station = glmReadOBJ("data/space_station_v01.obj");

		if(!station) exit(0);
		glmUnitize(station);
		glmFacetNormals(station);
		glmVertexNormals(station, 90.0);
	}

	if(objFlag == 1)
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, -10.0);
			glColor3f(0.0, 1.0, 0.0);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
			glBegin(GL_LINES);
				for (i = 0; i < 360; i++)
				{
					double angle = 6 * 3.14 * i/360;
					double x = cos(angle) * 3.3;
					double y = sin(angle) * 3.3;
					double z = cos(angle) * 2.0;
					glVertex3f(x, y, z);
				}
			glEnd();

			glPushMatrix();
				spaceStationX = cos(spaceStationSpin) * 3.3;
				spaceStationY = sin(spaceStationSpin) * 3.3;
				glTranslatef(spaceStationX, spaceStationY, spaceStationZ);
				glScalef(0.3, 0.3, 0.3);
				glRotatef(spin * 24.0, 1.0, 1.0, 0.0);
				glColor3f(1.0, 1.0, 1.0);
				glmDraw(station, GLM_SMOOTH);
			glPopMatrix();

			glPushMatrix();
				glColor3f(0.0, 1.0, 0.0);
				glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission );
				glTranslatef(spaceStationX, spaceStationY, spaceStationZ);
				glRotatef(spin * 360, 1.0, 1.0, 1.0);
				glBegin(GL_LINE_LOOP);
					for (i = 0; i < 360; i++)
					{
						double angle = 6 * 3.14 * i/360;
						double x = cos(angle) * 0.3;
						double y = sin(angle) * 0.3;
						glVertex3f(x, y, 0.0);
					}
				glEnd();
				glBegin(GL_LINE_LOOP);
					for (i = 0; i < 360; i++)
					{
						double angle = 6 * 3.14 * i/360;
						double x = cos(angle) * 0.3;
						double y = sin(angle) * 0.3;
						glVertex3f(x, y, x * 1.0);
					}
				glEnd();
				glBegin(GL_LINE_LOOP);
					for (i = 0; i < 360; i++)
					{
						double angle = 6 * 3.14 * i/360;
						double x = cos(angle) * 0.3;
						double y = sin(angle) * 0.3;
						glVertex3f(x, y, x * -1.0);
					}
				glEnd();
				glBegin(GL_LINE_LOOP);
					for (i = 0; i < 360; i++)
					{
						double angle = 7 * 3.14 * i/360;
						double x = cos(angle) * 0.3;
						double y = sin(angle) * 0.3;
						glVertex3f(x, y, 0.0);
					}
				glEnd();
			glPopMatrix();
		glPopMatrix();
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	if(rotate && rotateCamFlag == 1)
	{
		eyeX = vectorX + 10.0 * cos(phi) * sin(theta);
		eyeY = vectorY + 10.0 * sin(phi) * sin(theta);
		eyeZ = vectorZ + 10.0 * cos(theta);
	}

	gluLookAt(eyeX, eyeY, eyeZ, vectorX, vectorY, vectorZ, 0.0, 1.0, 0.0);

	spin += 0.01 * speed;

	/* ORBIT LINE SECTION */
	// MERCURY LINE
	glPushMatrix();
		glTranslatef(0.0, 0.0, -10.0);
		glColor3f(0.9, 0.5, 0.0);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		glBegin(GL_LINE_LOOP);
			for (i = 0; i < 360; i++)
			{
				double angle = 6 * 3.14 * i/360;
				double x = cos(angle) * 1.5;
				double y = sin(angle) * 1.5;
				glVertex3f(x, y, 0.0);
			}
		glEnd();
	glPopMatrix();

	// VENUS LINE
	glPushMatrix();
		glTranslatef(0.0, 0.0, -10.0);
		glColor3f(0.9, 0.5, 0.0);
		glBegin(GL_LINE_LOOP);
			for (i = 0; i < 360; i++)
			{
				double angle = 6 * 3.14 * i/360;
				double x = cos(angle) * 2;
				double y = sin(angle) * 2;
				glVertex3f(x, y, 0.0);
			}
		glEnd();
	glPopMatrix();

	// EARTH LINE
	glPushMatrix();
		glTranslatef(0.0, 0.0, -10.0);
		glColor3f(0.9, 0.5, 0.0);
		glBegin(GL_LINE_LOOP);
			for (i = 0; i < 360; i++)
			{
				double angle = 6 * 3.14 * i/360;
				double x = cos(angle) * 3;
				double y = sin(angle) * 3;
				glVertex3f(x, y, 0.0);
			}
		glEnd();
	glPopMatrix();

	// MARS LINE
	glPushMatrix();
		glTranslatef(0.0, 0.0, -10.0);
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINE_LOOP);
			for (i = 0; i < 360; i++)
			{
				double angle = 6 * 3.14 * i/360;
				double x = cos(angle) * 4.0;
				double y = sin(angle) * 4.0;
				glVertex3f(x, y, 0.0);
			}
		glEnd();
	glPopMatrix();

	// JUPITER LINE
	glPushMatrix();
		glTranslatef(0.0, 0.0, -10.0);
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINE_LOOP);
			for (i = 0; i < 360; i++)
			{
				double angle = 6 * 3.14 * i/360;
				double x = cos(angle) * 5.5;
				double y = sin(angle) * 5.5;
				glVertex3f(x, y, 0.0);
			}
		glEnd();
	glPopMatrix();

	// SATURN LINE
	glPushMatrix();
		glTranslatef(0.0, 0.0, -10.0);
		glColor3f(0.2, 0.2, 0.7);
		glBegin(GL_LINE_LOOP);
			for (i = 0; i < 360; i++)
			{
				double angle = 6 * 3.14 * i/360;
				double x = cos(angle) * 7.0;
				double y = sin(angle) * 7.0;
				glVertex3f(x, y, 0.0);
			}
		glEnd();
	glPopMatrix();

	// URANUS LINE
	glPushMatrix();
		glTranslatef(0.0, 0.0, -10.0);
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
			for (i = 0; i < 360; i++)
			{
				double angle = 6 * 3.14 * i/360;
				double x = cos(angle) * 8.5;
				double y = sin(angle) * 8.5;
				glVertex3f(x, y, 0.0);
			}
		glEnd();
	glPopMatrix();

	// NEPTUNE LINE
	glPushMatrix();
		glTranslatef(0.0, 0.0, -10.0);
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
			for (i = 0; i < 360; i++)
			{
				double angle = 6 * 3.14 * i/360;
				double x = cos(angle) * 11.0;
				double y = sin(angle) * 11.0;
				glVertex3f(x, y, 0.0);
			}
		glEnd();
	glPopMatrix();

/* PLANET DRAW SECTION */ 
	// Sun planet and orbit
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
		sphere = gluNewQuadric();
		gluQuadricNormals(sphere, GLU_SMOOTH);
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(0.0, 0.0, -10.0);
		glRotatef(spin * 10.0, 1.0, 0.0, 0.0);
		glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat );
		glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );
		// Material toggles
		if (dToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat );
			glMaterialfv( GL_FRONT, GL_SHININESS, no_mat );
		}
		else if (sToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, low_shininess );
		}
		else if (shToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );
		}
		// Draw Style Section
		if(solidFlag == 1)
		{
			gluQuadricTexture(sphere, GL_TRUE);
			gluQuadricDrawStyle(sphere, GLU_FILL);
		}
		else if(wireFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_LINE);
		}
		else if(pointFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_POINT);
		}
		gluSphere(sphere, 0.8, 50.0, 50.0);
		gluDeleteQuadric(sphere);
		// Sun snap section
		if (sunFlag == 1)
		{
			eyeX = 0.0;
			eyeY = 0.0;
			vectorX = 0.0;
			vectorY = 0.0;
		}
	glPopMatrix();
	
	// MERCURY planet and orbit
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();
		sphere = gluNewQuadric();
		gluQuadricNormals(sphere, GLU_SMOOTH);
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(merSpinX, merSpinY, -10.0);
		glRotatef(spin * 10.0, 1.0, 0.0, 0.0);
		glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat );
		glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );
		// Material toggles
		if (dToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat );
			glMaterialfv( GL_FRONT, GL_SHININESS, no_mat );
		}
		else if (sToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, low_shininess );
		}
		else if (shToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );
		}
		// Draw Style Section
		if(solidFlag == 1)
		{
			gluQuadricTexture(sphere, GL_TRUE);
			gluQuadricDrawStyle(sphere, GLU_FILL);
		}
		else if(wireFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_LINE);
		}
		else if(pointFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_POINT);
		}

		// Orbit
		if(spinFlag == 1)
		{
			merSpinX = cos(merSpin) * 1.5;
			merSpinY = sin(merSpin) * 1.5;
			merSpin = spin + merSpin / 12;
		}
		// Mercury Snap Section
		if (merFlag == 1)
		{
			eyeX = merSpinX;
			eyeY = merSpinY;
			vectorX = merSpinX;
			vectorY = merSpinY;
		}

		gluSphere(sphere, 0.12, 20.0, 20.0);
		gluDeleteQuadric(sphere);
	glPopMatrix();
	
	// VENUS planet and orbit
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glPushMatrix();
		sphere = gluNewQuadric();
		gluQuadricNormals(sphere, GLU_SMOOTH);
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(venSpinX, venSpinY, -10.0);
		glRotatef(spin * 10.0, 1.0, 0.0, 0.0);
		glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat );
		glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );
		// Material toggles
		if (dToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat );
			glMaterialfv( GL_FRONT, GL_SHININESS, no_mat );
		}
		else if (sToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, low_shininess );
		}
		else if (shToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );
		}
		// Draw Style Section
		if(solidFlag == 1)
		{
			gluQuadricTexture(sphere, GL_TRUE);
			gluQuadricDrawStyle(sphere, GLU_FILL);
		}
		else if(wireFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_LINE);
		}
		else if(pointFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_POINT);
		}

		// Orbit
		if(spinFlag == 1)
		{
			venSpinX = cos(venusSpin) * 2.0;
			venSpinY = sin(venusSpin) * 2.0;
			venusSpin = spin + venusSpin / 20;
		}
		// Venus section section
		if (venFlag == 1)
		{
			eyeX = venSpinX;
			eyeY = venSpinY;
			vectorX = venSpinX;
			vectorY = venSpinY;
		}
		gluSphere(sphere, 0.17, 20.0, 20.0);
		gluDeleteQuadric(sphere);
	glPopMatrix();

	// EARTH planet and orbit
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glPushMatrix();
		sphere = gluNewQuadric();
		gluQuadricNormals(sphere, GLU_SMOOTH);
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(earthSpinX, earthSpinY, -10.0);
		glRotatef(spin * 10.0, 1.0, 0.0, 0.0);
		glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat );
		glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );
		// Material toggles
		if (dToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat );
			glMaterialfv( GL_FRONT, GL_SHININESS, no_mat );
		}
		else if (sToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, low_shininess );
		}
		else if (shToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );
		}
		// Draw Style Section
		if(solidFlag == 1)
		{
			gluQuadricTexture(sphere, GL_TRUE);
			gluQuadricDrawStyle(sphere, GLU_FILL);
		}
		else if(wireFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_LINE);
		}
		else if(pointFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_POINT);
		}
		// Orbit
		if(spinFlag == 1)
		{
			earthSpinX = cos(earthSpin) * 3.0;
			earthSpinY = sin(earthSpin) * 3.0;
			earthSpin = spin + earthSpin / 24;
		}
		// Earth snap section
		if (earthFlag == 1)
		{
			eyeX = earthSpinX;
			eyeY = earthSpinY;
			vectorX = earthSpinX;
			vectorY = earthSpinY;
		}
		gluSphere(sphere, 0.2, 20.0, 20.0);
		gluDeleteQuadric(sphere);

		// Moon planet and orbit
		glBindTexture(GL_TEXTURE_2D, texture[10]);
		glPushMatrix();
			sphere = gluNewQuadric();
			glColor3f(0.8, 0.8, 0.8);
			gluQuadricNormals(sphere, GLU_SMOOTH);
			glTranslatef(earthSpinX / 12, earthSpinY / 12, 0.0);
			glRotatef(spin * 100.0, 0.0, 1.0, 1.0);
			glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat );
			glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );
			// Material toggles
			if (dToggle == 1)
			{
				glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
				glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat );
				glMaterialfv( GL_FRONT, GL_SHININESS, no_mat );
			}
			else if (sToggle == 1)
			{
				glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
				glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
				glMaterialfv( GL_FRONT, GL_SHININESS, low_shininess );
			}
			else if (shToggle == 1)
			{
				glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
				glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
				glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );
			}
			// Draw Style Section
			if(solidFlag == 1)
			{
				gluQuadricTexture(sphere, GL_TRUE);
				gluQuadricDrawStyle(sphere, GLU_FILL);
			}
			else if(wireFlag == 1)
			{
				gluQuadricTexture(sphere, GL_FALSE);
				gluQuadricDrawStyle(sphere, GLU_LINE);
			}
			else if(pointFlag == 1)
			{
				gluQuadricTexture(sphere, GL_FALSE);
				gluQuadricDrawStyle(sphere, GLU_POINT);
			}
			gluSphere(sphere, 0.05, 20.0, 20.0);
			gluDeleteQuadric(sphere);
		glPopMatrix();

	glPopMatrix();


	// MARS planet and orbit
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glPushMatrix();
		sphere = gluNewQuadric();
		gluQuadricNormals(sphere, GLU_SMOOTH);
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(marsSpinX, marsSpinY, -10.0);
		glRotatef(spin * 10.0, 1.0, 0.0, 0.0);
		glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat );
		glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );
		// Material toggles
		if (dToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat );
			glMaterialfv( GL_FRONT, GL_SHININESS, no_mat );
		}
		else if (sToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, low_shininess );
		}
		else if (shToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );
		}
		// Draw Style Section
		if(solidFlag == 1)
		{
			gluQuadricTexture(sphere, GL_TRUE);
			gluQuadricDrawStyle(sphere, GLU_FILL);
		}
		else if(wireFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_LINE);
		}
		else if(pointFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_POINT);
		}
		// Orbit
		if(spinFlag == 1)
		{
			marsSpinX = cos(marsSpin) * 4.0;
			marsSpinY = sin(marsSpin) * 4.0;
			marsSpin = spin + marsSpin / 32;
		}
		// Mars planet snap
		if (marsFlag == 1)
		{
			eyeX = marsSpinX;
			eyeY = marsSpinY;
			vectorX = marsSpinX;
			vectorY = marsSpinY;
		}
		gluSphere(sphere, 0.17, 20.0, 20.0);
		gluDeleteQuadric(sphere);
	glPopMatrix();

	// JUPITER planet and orbit
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glPushMatrix();
		sphere = gluNewQuadric();
		gluQuadricNormals(sphere, GLU_SMOOTH);
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(jupiterSpinX, jupiterSpinY, -10.0);
		glRotatef(spin * 10.0, 1.0, 0.0, 0.0);
		glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat );
		glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );
		// Material toggles
		if (dToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat );
			glMaterialfv( GL_FRONT, GL_SHININESS, no_mat );
		}
		else if (sToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, low_shininess );
		}
		else if (shToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );
		}
		// Draw Style Section
		if(solidFlag == 1)
		{
			gluQuadricTexture(sphere, GL_TRUE);
			gluQuadricDrawStyle(sphere, GLU_FILL);
		}
		else if(wireFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_LINE);
		}
		else if(pointFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_POINT);
		}
		// Orbit
		if(spinFlag == 1)
		{
			jupiterSpinX = cos(jupiterSpin) * 5.5;
			jupiterSpinY = sin(jupiterSpin) * 5.5;
			jupiterSpin = spin + jupiterSpin / 40;
		}
		// Jupiter planet snap
		if (jupiterFlag == 1)
		{
			eyeX = jupiterSpinX;
			eyeY = jupiterSpinY;
			vectorX = jupiterSpinX;
			vectorY = jupiterSpinY;
		}
		gluSphere(sphere, 0.65, 30.0, 30.0);
		gluDeleteQuadric(sphere);
	glPopMatrix();

	// SATURN planet and orbit
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glPushMatrix();
		sphere = gluNewQuadric();
		gluQuadricNormals(sphere, GLU_SMOOTH);
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(saturnSpinX, saturnSpinY, -10.0);
		glRotatef(spin * 10.0, 1.0, 0.0, 0.0);
		glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat );
		glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );
		// Material toggles
		if (dToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat );
			glMaterialfv( GL_FRONT, GL_SHININESS, no_mat );
		}
		else if (sToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, low_shininess );
		}
		else if (shToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );
		}
		// Draw Style Section
		if(solidFlag == 1)
		{
			gluQuadricTexture(sphere, GL_TRUE);
			gluQuadricDrawStyle(sphere, GLU_FILL);
		}
		else if(wireFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_LINE);
		}
		else if(pointFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_POINT);
		}
		// Orbit
		if(spinFlag == 1)
		{
			saturnSpinX = cos(saturnSpin) * 7.0;
			saturnSpinY = sin(saturnSpin) * 7.0;
			saturnSpin = spin + saturnSpin / 80;
		}
		// Saturn planet snap
		if (saturnFlag == 1)
		{
			eyeX = saturnSpinX;
			eyeY = saturnSpinY;
			vectorX = saturnSpinX;
			vectorY = saturnSpinY;
		}
		gluSphere(sphere, 0.6, 30.0, 30.0);
		gluDeleteQuadric(sphere);
	glPopMatrix();

	// URANUS planet and orbit
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glPushMatrix();
		sphere = gluNewQuadric();
		gluQuadricNormals(sphere, GLU_SMOOTH);
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(uranusSpinX, uranusSpinY, -10.0);
		glRotatef(spin * 10.0, 1.0, 0.0, 0.0);
		glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat );
		glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );
		// Material toggles
		if (dToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat );
			glMaterialfv( GL_FRONT, GL_SHININESS, no_mat );
		}
		else if (sToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, low_shininess );
		}
		else if (shToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );
		}
		// Draw Style Section
		if(solidFlag == 1)
		{
			gluQuadricTexture(sphere, GL_TRUE);
			gluQuadricDrawStyle(sphere, GLU_FILL);
		}
		else if(wireFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_LINE);
		}
		else if(pointFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_POINT);
		}
		// Orbit
		if(spinFlag == 1)
		{
			uranusSpinX = cos(uranusSpin) * 8.5;
			uranusSpinY = sin(uranusSpin) * 8.5;
			uranusSpin = spin + uranusSpin / 180;
		}
		// Uranus planet snap
		if (uranusFlag == 1)
		{
			eyeX = uranusSpinX;
			eyeY = uranusSpinY;
			vectorX = uranusSpinX;
			vectorY = uranusSpinY;
		}
		gluSphere(sphere, 0.35, 35.0, 35.0);
		gluDeleteQuadric(sphere);
	glPopMatrix();

	// NEPTUNE planet and orbit
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glPushMatrix();
		sphere = gluNewQuadric();
		gluQuadricNormals(sphere, GLU_SMOOTH);
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(neptuneSpinX, neptuneSpinY, -10.0);
		glRotatef(spin * 10.0, 1.0, 0.0, 0.0);
		glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat );
		glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );
		// Material toggles
		if (dToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat );
			glMaterialfv( GL_FRONT, GL_SHININESS, no_mat );
		}
		else if (sToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, low_shininess );
		}
		else if (shToggle == 1)
		{
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
			glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );
		}
		// Draw Style Section
		if(solidFlag == 1)
		{
			gluQuadricTexture(sphere, GL_TRUE);
			gluQuadricDrawStyle(sphere, GLU_FILL);
		}
		else if(wireFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_LINE);
		}
		else if(pointFlag == 1)
		{
			gluQuadricTexture(sphere, GL_FALSE);
			gluQuadricDrawStyle(sphere, GLU_POINT);
		}
		if(spinFlag == 1)
		{
			neptuneSpinX = cos(neptuneSpin) * 11.0;
			neptuneSpinY = sin(neptuneSpin) * 11.0;
			neptuneSpin = spin + neptuneSpin / 380;
		}
		// Neptune planet snap
		if (neptuneFlag == 1)
		{
			eyeX = neptuneSpinX;
			eyeY = neptuneSpinY;
			vectorX = neptuneSpinX;
			vectorY = neptuneSpinY;
		}
		gluSphere(sphere, 0.35, 30.0, 30.0);
		gluDeleteQuadric(sphere);
	glPopMatrix();

	//glPushMatrix();
	//	sphere = gluNewQuadric();
	//	glColor3f(0.0, 0.0, 1.0);
	//	glTranslatef(plutoX, plutoY, plutoZ);
	//	glRotatef(spin, 1.0, 0.0, 1.0);
	//	glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat );
	//	glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );
	//	if(spinFlag == 1)
	//	{
	//		plutoX = cos(plutoSpin) * 12.0;
	//		plutoY = sin(plutoSpin) * 12.0;
	//		plutoZ = cos(plutoSpin) * 12.0;
	//		plutoSpin = spin + plutoSpin / 400;
	//	}
	//	gluSphere(sphere, 0.10, 20.0, 20.0);
	//	gluDeleteQuadric(sphere);
	//glPopMatrix();

	// Draw stars
	glPushMatrix();
		sphere = gluNewQuadric();
		gluQuadricNormals(sphere, GLU_SMOOTH);
		
		glTranslatef(0.0, 0.0, -10.0);
		gluQuadricTexture(sphere, GL_FALSE);
		gluQuadricDrawStyle(sphere, GLU_POINT);
		glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission );
		for(j = 10.0; j < 20.0; j++)
		{
			glColor3f(R, G, B);
			glRotatef(45.0, j, j, 0.0);
			gluSphere(sphere, j, 10.0, 10.0);
		}
		gluDeleteQuadric(sphere);
	glPopMatrix();

	drawmodel();
	glutSwapBuffers();
}

void zoomDisplay(void)
{
	if(zoomFlag == 1)
	{
		eyeZ -= 2.0 * (zoomSpeed);
		vectorZ = -10.0;
		if (eyeZ <= -7.0)
		{
			zoomFlag = 0;
		}
	}
	else if(zoomFlag == 2)
	{
		eyeZ += 2.0 * (zoomSpeed);
		vectorZ = -10.0;
		if (eyeZ >= 10.0)
		{
			zoomFlag = 0;
		}
	}
	else if(rotateFlag == 1)
	{
		eyeX = 10.0 * cos(angle);
		eyeY = 14.0 * cos(angle);
		eyeZ = 14.0 * sin(angle);
		vectorZ = -10.0;
		angle += 0.005;
	}
	glutPostRedisplay();
}

int init(void)
{
	// Load textures at start of program
	if(!LoadGLTextures())
	{
		return FALSE;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);

	glClearColor(0.0, 0.0, 0.0, 0.0); // Background color
	glShadeModel(GL_SMOOTH);

	glColorMaterial(GL_FRONT, GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
    
	return TRUE;
}	

void reshape(int width, int height)
{
	glViewport(0.0, 0.0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, ((GLfloat) width) / (GLfloat) height, 1.0, 600.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mainEvents(int option)
{
	switch(option)
	{
		default:
			break;
	}
}

void styleEvents(int option)
{
	switch(option)
	{
		case SOLID:
			solidFlag = 1;
			pointFlag = 0;
			wireFlag = 0;
			break;
		case POINT:
			solidFlag = 0;
			pointFlag = 1;
			wireFlag = 0;
			break;
		case WIRE:
			solidFlag = 0;
			pointFlag = 0;
			wireFlag = 1;
			break;
		default:
			break;
	}
}

void planetEvents(int option)
{
	switch(option)
	{
		case SUN:
			sunFlag = 1;
			merFlag = 0;
			venFlag = 0;
			earthFlag = 0;
			marsFlag = 0;
			jupiterFlag = 0;
			saturnFlag = 0;
			uranusFlag = 0;
			neptuneFlag = 0;
			break;
		case MERCURY:
			sunFlag = 0;
			merFlag = 1;
			venFlag = 0;
			earthFlag = 0;
			marsFlag = 0;
			jupiterFlag = 0;
			saturnFlag = 0;
			uranusFlag = 0;
			neptuneFlag = 0;
			break;
		case VENUS:
			sunFlag = 0;
			merFlag = 0;
			venFlag = 1;
			earthFlag = 0;
			marsFlag = 0;
			jupiterFlag = 0;
			saturnFlag = 0;
			uranusFlag = 0;
			neptuneFlag = 0;
			break;
		case EARTH:
			sunFlag = 0;
			merFlag = 0;
			venFlag = 0;
			earthFlag = 1;
			marsFlag = 0;
			jupiterFlag = 0;
			saturnFlag = 0;
			uranusFlag = 0;
			neptuneFlag = 0;			
			break;
		case MARS:
			sunFlag = 0;
			merFlag = 0;
			venFlag = 0;
			earthFlag = 0;
			marsFlag = 1;
			jupiterFlag = 0;
			saturnFlag = 0;
			uranusFlag = 0;
			neptuneFlag = 0;				
			break;
		case JUPITER:
			sunFlag = 0;
			merFlag = 0;
			venFlag = 0;
			earthFlag = 0;
			marsFlag = 0;
			jupiterFlag = 1;
			saturnFlag = 0;
			uranusFlag = 0;
			neptuneFlag = 0;	
			break;
		case SATURN:
			sunFlag = 0;
			merFlag = 0;
			venFlag = 0;
			earthFlag = 0;
			marsFlag = 0;
			jupiterFlag = 0;
			saturnFlag = 1;
			uranusFlag = 0;
			neptuneFlag = 0;	
			break;
		case URANUS:
			sunFlag = 0;
			merFlag = 0;
			venFlag = 0;
			earthFlag = 0;
			marsFlag = 0;
			jupiterFlag = 0;
			saturnFlag = 0;
			uranusFlag = 1;
			neptuneFlag = 0;	
			break;
		case NEPTUNE:
			sunFlag = 0;
			merFlag = 0;
			venFlag = 0;
			earthFlag = 0;
			marsFlag = 0;
			jupiterFlag = 0;
			saturnFlag = 0;
			uranusFlag = 0;
			neptuneFlag = 1;	
			break;
		default:
			break;
	}
}

void matEvents(int option)
{
	switch(option)
	{
		case DIFFUSE:
			dToggle = 1;
			sToggle = 0;
			shToggle = 0;
			break;
		case SPECULAR:
			dToggle = 0;
			sToggle = 1;
			shToggle = 0;
			break;
		case SHININESS:
			dToggle = 0;
			sToggle = 0;
			shToggle = 1;
		default:
			break;
	}
}

void createGLUTMenus()
{
	int menu;
	int stylemenu;
	int matmenu;
	int planetmenu;

	matmenu = glutCreateMenu(matEvents);
	glutAddMenuEntry("Diffuse", DIFFUSE);
	glutAddMenuEntry("Specular", SPECULAR);
	glutAddMenuEntry("Shininess", SHININESS);
	
	stylemenu = glutCreateMenu(styleEvents);
	glutAddMenuEntry("Solid", SOLID);
	glutAddMenuEntry("Points", POINT);
	glutAddMenuEntry("Wireframe", WIRE);

	planetmenu = glutCreateMenu(planetEvents);
	glutAddMenuEntry("Sun", SUN);
	glutAddMenuEntry("Mercury", MERCURY);
	glutAddMenuEntry("Venus", VENUS);
	glutAddMenuEntry("Earth", EARTH);
	glutAddMenuEntry("Mars", MARS);
	glutAddMenuEntry("Jupiter", JUPITER);
	glutAddMenuEntry("Saturn", SATURN);
	glutAddMenuEntry("Uranus", URANUS);
	glutAddMenuEntry("Neptune", NEPTUNE);

	menu = glutCreateMenu(mainEvents);
	glutAddSubMenu("Style", stylemenu);
	glutAddSubMenu("Planets", planetmenu);
	glutAddSubMenu("Materials", matmenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:
			exit(0);
			break;
		case 't':
			glEnable(GL_TEXTURE_2D);
			break;
		case 'T':
			glDisable(GL_TEXTURE_2D);
			break;
		case 'l':
			glEnable(GL_LIGHT0);
			lightFlag = 1;
			break;
		case 'L':
			glDisable(GL_LIGHT0);
			lightFlag = 0;
			break;
		case '+':
			speed += 0.1;
			break;
		case '-':
			speed -= 0.1;
			break;
		case 'q':
			growFlag = 1;
			objFlag = 1;
			break;
		case 'Q':
			growFlag = 0;
			objFlag = 0;
			break;
		default:
			break;
	}
}

void processSpecialFunc(int key, int x, int y)
{
	double angle = 6 * 3.14 * i/360;

	switch(key)
	{
		case GLUT_KEY_F1:
			rotateFlag = 1;
			zoomFlag = 0;
			break;
		case GLUT_KEY_F2:
			rotateFlag = 2;
			zoomFlag = 0;
			break;
		case GLUT_KEY_F3:
			zoomFlag = 1;
			rotateFlag = 0;
			break;
		case GLUT_KEY_F4:
			zoomFlag = 2;
			rotateFlag = 0;
			break;
		case GLUT_KEY_F5:
			eyeX = 0.0;
			eyeY = 0.0;
			eyeZ = 0.0;
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP:
			spaceStationX = cos(spaceStationSpin) * 3.3;
			spaceStationY = sin(spaceStationSpin) * 3.3;
			spaceStationZ = cos(spaceStationSpin) * 2.0;
			spaceStationSpin = spin + spaceStationSpin / 360;
			break;
		default:
			break;
	}
}

void mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_UP)
		{
			rotate = FALSE;
			rotateCamFlag = 0;
			eyeX = 0.0;
			eyeY = 0.0;
			eyeZ = 0.0;
		}
		else
		{
			oldX = x;
			oldY = y;
			rotate = TRUE;
			rotateCamFlag = 1;
		}
	}
}

void mouseMove(int x, int y)
{
	if(rotate)
	{
		theta += (x - oldX) * 0.005;
		phi += (y - oldY) * 0.005;
	}

	oldX = x;
	oldY = y;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Final Project: Solar System");

	glutIdleFunc(zoomDisplay);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(processSpecialFunc);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	createGLUTMenus();
	init();

	glutMainLoop();
	return 0;
}