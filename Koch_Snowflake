/***
Koch's Snowflake
 ***/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
static FILE *ps_file;
static double g_x, g_y;
static double dir;

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

typedef struct {
    double g_x, g_y, dir;
} Turtle;

// Starts a new graph with given filename
void start( const char *filename );

// Ends the graph
void end( void );

// Draws a line of given length (in millimeters)
void draw( double length );

// Makes a move of given length (in millimeters), without drawing
void move( double length );

// Turns right of a given angle (in degrees)
void turn( double ang );

// Save the current position and direction into structure t
void save_state(Turtle *t);

// Restore previously saved position and direction from structure t
void restore_state(const Turtle *t);

// Set color (r, g, b); each component must be in [0,1]
void setcolor(double r, double g, double b);

void start( const char *filename ) {
    if ((ps_file = fopen( filename, "wt" )) == NULL) {
        fprintf(stderr, "Cannot open %s. Stop\n", filename);
        exit(EXIT_FAILURE);
    }
    fprintf( ps_file, "%%!PS-Adobe-2.0\n" );
    g_x = 2*72;
    g_y = 7*72;
    fprintf( ps_file, "%d %d moveto\n", (int)(g_x), (int)(g_y) );
    dir = 0.0;
}

void end( void ) {
    fprintf( ps_file, "stroke\nshowpage\n" );
    fclose( ps_file );
}

void draw( double length ) {
    length /= 0.352777778;
    g_x += length * cos( dir );
    g_y += length * sin( dir );
    fprintf( ps_file, "%d %d lineto\n", (int)(g_x), (int)(g_y) );
}

void move( double length ) {
    length /= 0.352777778;
    g_x += length * cos( dir );
    g_y += length * sin( dir );
    fprintf( ps_file, "%d %d moveto\n", (int)(g_x), (int)(g_y) );
}

void turn( double ang ) {
    dir -= M_PI * ang / 180.0;
}

void save_state(Turtle *t) {
    assert(t != NULL);
    t->g_x = g_x;
    t->g_y = g_y;
    t->dir = dir;
}

void setcolor( double r, double g, double b ) {
    fprintf(ps_file, "stroke\n%f %f %f setrgbcolor\n", r, g, b);
    move(0); /* to start a new path */
}

void restore_state(const Turtle *t) {
    assert(t != NULL);
    g_x = t->g_x;
    g_y = t->g_y;
    dir = t->dir;
    fprintf( ps_file, "%d %d moveto\n", (int)g_x, (int)g_y);
}


// Draw the Koch curve of order n and length x
void koch(double x, int n) {
    if (n == 0) {
        draw(x);
    } else {
        koch(x/3, n-1);
        turn(-60);
        koch(x/3, n-1);
        turn(120);
        koch(x/3, n-1);
        turn(-60);
        koch(x/3, n-1);
    }
}

void fractal_tree(double x, int n) {
    if (n > 0) {
        Turtle t;
        draw(x);
        save_state(&t);
        turn(-30);
        fractal_tree(x*0.7, n-1);
        restore_state(&t);
        turn(30);
        fractal_tree(x*0.7, n-1);
    }
}

int main( void ) {
    const int n = 4;
    int i;
    start("koch-curve.ps");
    for (i=0; i<4; i++) {
        koch(50, i);
        move(-50); turn(-90); move(15); turn(90);
    }
    koch(50.0/3, i-1);
    turn(-60);
    setcolor(1, 0, 0);
    koch(50.0/3, i-1);
    turn(120);
    setcolor(0, 1, 0);
    koch(50.0/3, i-1);
    turn(-60);
    setcolor(0, 0, 1);
    koch(50.0/3, i-1);
    end();

    start("koch-snowflake.ps");
    setcolor(1, 0, 0); koch(50, n);
    turn(120);
    setcolor(0, 1, 0); koch(50, n);
    turn(120);
    setcolor(0, 0, 1); koch(50, n);
    end();

    start("fractal-tree.ps");
    turn(-90);
    fractal_tree(20, 6);
    end();
    return EXIT_SUCCESS;
}
