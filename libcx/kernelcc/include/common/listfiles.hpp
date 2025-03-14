#ifndef __LIST_FILES
#define __LIST_FILES



#include <typing.hpp>
#include <types.h>
#include <common/init.hpp>


class Retain{

    public:
    const char* filename;
    INTEGER chunk_size;
    const char* content;
        Retain(const char* filename,INTEGER chunk_size,const char* content){
            this->filename = filename;
            this->chunk_size = chunk_size;
            this->content = content;

        }    
    public:
        VOID retention(const char* file_name,INTEGER size,const char* content){
                    const char* file = file_name;
            if (!file_name || !size){
                Novanix::system::printk(VGA_COLOR_WHITE,"ERROR!",1);
            }
            else{
                Novanix::system::printk(VGA_COLOR_WHITE,"Creating file: ",1);
                Novanix::system::printk(VGA_COLOR_WHITE,file_name,1);
                Novanix::system::printk(VGA_COLOR_WHITE," with size: ",1);
                Novanix::system::printk(VGA_COLOR_WHITE,stringify(size),1);
                Novanix::system::printk(VGA_COLOR_WHITE," and content: ",1);
                Novanix::system::printk(VGA_COLOR_WHITE,content,1);

            }
                }
    
};  


Retain create_file(const char* file_name,INTEGER size,const char* content){
    Retain file(file_name,size,content);
    file.retention(file_name,size,content);
    RET file;
}





#endif /*__LIST_FILES*/