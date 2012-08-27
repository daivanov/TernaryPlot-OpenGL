/*
 * Copyright 2012 Daniil Ivanov <daniil.ivanov@gmail.com>
 *
 * This file is part of TernaryPlot-OpenGL.
 *
 * TernaryPlot-OpenGL is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * TernaryPlot-OpenGL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with TernaryPlot-OpenGL. If not, see http://www.gnu.org/licenses/.
 */

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

static double sin60;
static double cos60 = 0.5;

void drawField(double width, double height)
{
    double size = width / 1.2;
    double vborder = (height - size * sin60) / 2;
    double x1 = 0.1 * size;
    double x2 = 1.1 * size;
    double x3 = 0.6 * size;
    double y1 = vborder;
    double y2 = vborder;
    double y3 = vborder + size * sin60;

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);

    glBegin(GL_LINE_LOOP);
    glVertex2f(0.1 * size, vborder);
    glVertex2f(1.1 * size, vborder);
    glVertex2f(0.6 * size, vborder + size * sin60);
    glEnd();

    glLineWidth(1.0);
    for (double frac = 0.1; frac <= 0.5; frac += 0.1) {
        glBegin(GL_LINE_LOOP);
        glVertex2f(frac * x1 + (1 - frac) * x2, frac * y1 + (1 - frac) * y2);
        glVertex2f((1-frac) * x2 + frac * x3, (1-frac) * y2 + frac * y3);
        glVertex2f(frac * x3 + (1-frac) * x1, frac * y3 + (1-frac) * y1);
        glVertex2f((1-frac) * x1 + frac * x2, (1-frac) * y1 + frac * y2);
        glVertex2f(frac * x2 + (1-frac) * x3, frac * y2 + (1-frac) * y3);
        glVertex2f((1-frac) * x3 + frac * x1, (1-frac) * y3 + frac * y1);
        glEnd();
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawField(10.0, 10.0);

    glFlush();
}

void reshape(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    glLoadIdentity();
    if (newWidth > newHeight) {
        GLdouble dx = 10 * ((GLdouble)newWidth / newHeight - 1.0) / 2;
        glOrtho(-dx, 10.0 + dx, 0.0, 10.0, -1.0, 1.0);
    } else {
        GLdouble dy = 10 * ((GLdouble)newHeight / newWidth - 1.0) / 2;
        glOrtho(0.0, 10.0, -dy, 10.0 + dy, -1.0, 1.0);
    }
}

int main(int argc, char **argv)
{
    sin60 = sqrt(3)/2;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(300,300);
    glutCreateWindow ("Triangle");

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
