
#define TABLE_SIZE 26

typedef struct element_t{
    int pos;
    bool repeated;
}element_t;

typedef struct hashmap{
    element_t* table[TABLE_SIZE];
}hashmap_t;

hashmap_t* create_hashmap() {
    hashmap_t* map = malloc(sizeof(hashmap_t));
    for (int i = 0; i < TABLE_SIZE; i++)
        map->table[i] = NULL;
    return map;
}

int hash(char c) {
    return c - 'a';
}

void hashmap_put(hashmap_t* map, char c, int pos){
    int idx = hash(c);
    element_t* cur = map->table[idx];

    if(cur != NULL){
        cur->repeated = true;
        return;
    }

    element_t* new_elem = malloc(sizeof(element_t));
    new_elem->repeated  = false;
    new_elem->pos       = pos;
    map->table[idx]     = new_elem;
}

int firstUniqChar(char* s) {
    //will have to go through the whole string
    //create a hashmap consisting of every character in string
    //size will be 26
    //will be arranged accroding to appearence
    //no knowledge of length

    int pos = 0;
    int result = -1;
    hashmap_t* map = create_hashmap();

    while(s[pos] != '\0'){
        //insert the character to the hashmap*
        hashmap_put(map, s[pos], pos);
        //increment to the next character
        pos++;
    }

    //go through hashmap element by element, the first character that has a false in the repeating field is returned
    for(int i = 0; i < 26; i++){
        if(map->table[i] != NULL && map->table[i]->repeated == false){
            if(result == -1 || result > map->table[i]->pos){
                result = map->table[i]->pos;
            }
        }
    }

    return result;
}