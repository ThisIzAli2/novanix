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