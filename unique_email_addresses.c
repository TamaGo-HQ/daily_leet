#define TABLE_SIZE 50

char* is_valid(char* email){
    int i = 0;
    char* buffer = malloc(strlen(email) + 1); // max possible size
    int len_buffer = 0;

    while(email[i] != '@'&& email[i] != '+'){
        if(email[i] != '.'){
            buffer[len_buffer] = email[i];
            len_buffer++;
        }
        i++;
    }
    int len_domain = 0;
    if(email[i] == '+'){
        while(email[i] != '@'){
            i++;
        }
    }
    while(email[i] != '\0'){
        buffer[len_buffer] = email[i];
        len_buffer++;
        len_domain++;
        i++;
    }
    buffer[len_buffer] = '\0';
    if(len_domain < 4) return NULL;
    return buffer;
}

 typedef struct element_t{
    char* email;
    struct element_t* next;
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

// DJ2B hash function
unsigned long hash(char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash % TABLE_SIZE;
}

bool hashmap_put(hashmap_t* map, char* email) {
    unsigned int idx = hash(email);
    element_t* cur = map->table[idx];

    // Look for existing key
    while (cur != NULL) {
        if (strcmp(cur->email, email) == 0) {
            return false; // Key already exists, do nothing
        }
        cur = cur->next;
    }

    // Create new element and insert at head of list
    element_t* new_elem = malloc(sizeof(element_t));
    new_elem->email = malloc(strlen(email) + 1);
    strcpy(new_elem->email, email);
    new_elem->next = map->table[idx];
    map->table[idx] = new_elem;
    return true;
}

void free_hashmap(hashmap_t* map) {
    if (!map) return;

    for (int i = 0; i < TABLE_SIZE; i++) {
        element_t* cur = map->table[i];
        while (cur != NULL) {
            element_t* next = cur->next;
            free(cur->email); // free the string
            free(cur);        // free the node
            cur = next;
        }
        map->table[i] = NULL;
    }

    free(map); // free the hashmap struct
}

int numUniqueEmails(char** emails, int emailsSize) {
    //for all emails
        //check validity
        //put in hashmap // it all comes down to the hash, all equivalent emails need to map to one
        //put return wether unique or not
        //if unique increment
    int num_unique = 0;
    hashmap_t* map = create_hashmap();
    for(int i = 0; i < emailsSize; i++){
        char* final_email = is_valid(emails[i]);
        if(final_email != NULL){
            bool is_unique = hashmap_put(map, final_email);
            if(is_unique == true) num_unique++;
        }
        free(final_email);
    }
    free(map);
    return num_unique;
}