#include <stdio.h>
#include <stdlib.h>

#define N 11 // arena size: 11x11 grid (0 to 10)

// movement in 4 directions: north, east, south, west
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

// structure to hold a position and its history
typedef struct {
    int x, y;      // current position
    int dist;      // steps taken from start
    int px, py;    // previous position (to trace the path)
} Point;

// queue for bfs
Point queue[N * N];
int front = 0, rear = 0;

// add a point to the queue
void enqueue(Point p) 
{
    queue[rear++] = p;
}

// take a point from the queue
Point dequeue() 
{
    return queue[front++];
}

// check if a point is within the arena boundaries
int is_valid(int x, int y) 
{
    return x >= 0 && x < N && y >= 0 && y < N;
}

// initialize the arena with all positions marked safe (1)
void create_map(int arena[N][N]) 
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            arena[i][j] = 1;
}

// read obstacle positions from file and mark them in the arena
void load_obstacles(int arena[N][N], const char* filename) 
{
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("can't open file\n");
        exit(1);
    }

    int n, e, s, w;
    while (fscanf(f, "%d %d %d %d", &n, &e, &s, &w) != EOF) 
    {
        // calculate final obstacle position based on movement from origin
        int cx = 0, cy = 0;
        cx -= n; cy += e;
        cx += s; cy -= w;

        if (is_valid(cx, cy))
            arena[cx][cy] = 0; // mark as obstacle
    }

    fclose(f);
}

// print the entire arena with 1s, 0s, and path marked as *
void print_arena(int arena[N][N]) 
{
    printf("arena map:\n");
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            if (arena[i][j] == -1)
                printf("* "); // path
            else
                printf("%d ", arena[i][j]); // safe or obstacle
        }
        printf("\n");
    }
}

// find the shortest path using bfs and trace the route back
int shortest_path(int arena[N][N]) 
{
    int visited[N][N] = {0};
    Point parent[N][N]; // to trace each cell's parent

    Point start = {0, 0, 0, -1, -1}; // starting at (0,0)
    enqueue(start);
    visited[0][0] = 1;
    parent[0][0] = start;

    Point end;
    int found = 0;

    while (front < rear) 
    {
        Point p = dequeue();

        // check if destination is reached
        if (p.x == 10 && p.y == 10) 
        {
            end = p;
            found = 1;
            break;
        }

        // explore all 4 directions
        for (int i = 0; i < 4; i++) 
        {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];

            if (is_valid(nx, ny) && arena[nx][ny] == 1 && !visited[nx][ny]) 
            {
                visited[nx][ny] = 1;
                Point next = {nx, ny, p.dist + 1, p.x, p.y};
                parent[nx][ny] = next;
                enqueue(next);
            }
        }
    }

    // if no path found, return -1
    if (!found) return -1;

    // trace the shortest path back from destination to start
    Point trace = end;
    while (trace.px != -1 && trace.py != -1) 
    {
        arena[trace.x][trace.y] = -1; // mark path with -1
        trace = parent[trace.px][trace.py];
    }
    arena[0][0] = -1; // mark the starting point as part of path

    return end.dist; // return total steps taken
}

int main() 
{
    int arena[N][N];

    create_map(arena);                  // set all positions to safe
    load_obstacles(arena, "sample.txt"); // read obstacles from file

    int steps = shortest_path(arena);   // find the shortest route

    if (steps != -1) 
    {
        printf("shortest path is %d steps\n", steps);
        print_arena(arena);             // print the arena with path
    } 
    else 
    {
        printf("no path found\n");
        print_arena(arena);             // still print arena for reference
    }

    return 0;
}