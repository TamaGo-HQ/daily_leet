
void dfs(char** grid, int rows, int cols, int i, int j){
    // check case : out of bounds
    if (i < 0 || i >= rows || j < 0 || j >= cols){
        return;
    }

    // check case : not land (either '0' or already visited)
    if(grid[i][j] != '1'){
        return;
    }
    
    //mark as visited
    grid[i][j] = '0';

    // Explore all 4 directions
    dfs(grid, rows, cols, i + 1, j);  // down
    dfs(grid, rows, cols, i - 1, j);  // up
    dfs(grid, rows, cols, i, j + 1);  // right
    dfs(grid, rows, cols, i, j - 1);  // left    
}

int numIslands(char** grid, int gridSize, int* gridColSize) {

    // step 1 : check intputs
    // step 2 : go through all island
    // step 3 : create dfs helper function
    // step 4 : call dfs from main function
    if(grid == NULL || gridSize == 0){
        return 0;
    }

    int rows = gridSize;
    int cols = gridColSize[0];
    int count = 0;

    // loop through every cell
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++){
            if (grid[i][j] == '1'){
                count++; //found a new island snipet!
                //mark entire island as visited using DFS
                dfs(grid, rows, cols, i, j);
            }
        }
    }

    return count;
}