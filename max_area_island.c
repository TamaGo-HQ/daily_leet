
void maxAreaOfIslandHelper(int** grid, int rows, int cols, int i, int j, int* area){
    // check case : out of bounds
    if (i < 0 || i >= rows || j < 0 || j >= cols){
        return;
    }

    // check case : not land (either '0' or already visited)
    if(grid[i][j] != 1){
        return;
    }
    
    //mark as visited
    (*area)++;
    grid[i][j] = 0;

    // Explore all 4 directions
    maxAreaOfIslandHelper(grid, rows, cols, i + 1, j, area);  // down
    maxAreaOfIslandHelper(grid, rows, cols, i - 1, j, area);  // up
    maxAreaOfIslandHelper(grid, rows, cols, i, j + 1, area);  // right
    maxAreaOfIslandHelper(grid, rows, cols, i, j - 1, area);  // left    
}

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize) {

    // step 1 : check inputs
    // step 2 : detect first piece of island
    // step 3 : dfs calculates depth of that island
    // step 4 : if area of new island bigger than last island, update max

    if(grid == NULL || gridSize == 0){
        return 0;
    }

    int rows = gridSize;
    int cols = gridColSize[0];
    //----int max_area[2500];
    int max_area = 0;

    // loop through every cell
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++){
            if (grid[i][j] == 1){
                //mark entire island as visited using DFS
                int area = 0;
                maxAreaOfIslandHelper(grid, rows, cols, i, j, &area);
                if(area > max_area) { max_area = area;}
                //----dfs(grid, rows, cols, i, j, &max_area[(i*cols) + j]);
            }
        }
    }

    ////---- for(int i = 0; i < 100; i++){
    ////----    printf(" area of island that start at %d : %d \n", i, max_area[i]);
    ////---- }

    return max_area;
}
