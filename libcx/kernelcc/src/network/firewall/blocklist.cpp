#include <network/firewall/blocklist.h>



Node* allocate_node(){
    for (int i = 0; i < MAX_FIREWALL_IPS;i++){
        if (node_used[i] == 0){
            node_used[i] = 1;
            node_pool[i].next = 0;
            return &node_pool[i];
        }
    }
    return 0;
}

void free_node(Node* node) {
    int index = node - node_pool; // pointer arithmetic
    if (index >= 0 && index < MAX_FIREWALL_IPS) {
        node_used[index] = 0;
    }
}

// Head of the firewall block list

// Append an IP to the list
int firewall_append(ip_t ip) {
    Node* new_node = allocate_node();
    if (new_node == 0)
        return -1; // allocation failed

    new_node->ip = ip;
    new_node->next = 0;

    if (firewall_list == 0) {
        firewall_list = new_node;
    } else {
        Node* cur = firewall_list;
        while (cur->next != 0)
            cur = cur->next;
        cur->next = new_node;
    }
    return 0; // success
}

// Remove an IP from the list, return 0 if found and removed, -1 if not found
int firewall_remove(ip_t ip) {
    Node* cur = firewall_list;
    Node* prev = 0;

    while (cur != 0) {
        if (cur->ip == ip) {
            if (prev == 0) {
                firewall_list = cur->next;
            } else {
                prev->next = cur->next;
            }
            free_node(cur);
            return 0;
        }
        prev = cur;
        cur = cur->next;
    }
    return -1; // not found
}

// Check if an IP is blocked (returns 1 if blocked, 0 otherwise)
int firewall_check(ip_t ip) {
    Node* cur = firewall_list;
    while (cur != 0) {
        if (cur->ip == ip) {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

int search_for_ip(ip_t ip){
    Node* current = firewall_list;
    while (current != 0){
        if (current->ip == ip){
            return 1;
        } else{
            return 0;
        }
    }
    return 0;
}