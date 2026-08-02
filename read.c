#include"common.h"
#include"read.h"


//function definitioncd

void read_frame(FILE*fp)
{
    char frame_id[5];
    fread(frame_id,1,4,fp);
    frame_id[4]='\0';
    //printf("Frame ID : %s\n",frame_id);
    unsigned char size[4];
    fread(size,1,4,fp);
    int frame_size=(size[0]<<24)|(size[1]<<16)|(size[2]<<8)|size[3];
    //printf("Frame Size:%d\n",frame_size);
    fseek(fp,2,SEEK_CUR);
    char encoding;
    fread(&encoding,1,1,fp);
    char data[100];
    fread(data,1,frame_size-1,fp);
    data[frame_size-1]='\0';
    //comparing and printing output using frame id
    if(strcmp(frame_id,"TIT2")==0)
    {
        printf(CYAN"|"RESET YELLOW" %-20s " RESET CYAN "|" RESET GREEN " %-30s "RESET CYAN "|\n"RESET,"Title",data);
    }
    
    else if(strcmp(frame_id,"TPE1")==0)
    {
        printf(CYAN"|"RESET YELLOW" %-20s " RESET CYAN "|" RESET GREEN " %-30s "RESET CYAN "|\n"RESET,"Artist",data);
    }
    else if(strcmp(frame_id,"TALB")==0)
    {
        printf(CYAN"|"RESET YELLOW" %-20s " RESET CYAN "|" RESET GREEN " %-30s "RESET CYAN "|\n"RESET,"Album",data);
    }
    else if(strcmp(frame_id,"TYER")==0)
    {
        printf(CYAN"|"RESET YELLOW" %-20s " RESET CYAN "|" RESET GREEN " %-30s "RESET CYAN "|\n"RESET,"Year",data);
         
    }
    else if(strcmp(frame_id,"TCON")==0)
    {
        printf(CYAN"|"RESET YELLOW" %-20s " RESET CYAN "|" RESET GREEN " %-30s "RESET CYAN "|\n"RESET,"Content",data);
       
        
    }
    else if(strcmp(frame_id,"TCOM")==0)
    {
        printf(CYAN"|"RESET YELLOW" %-20s " RESET CYAN "|" RESET GREEN " %-30s "RESET CYAN "|\n"RESET,"Composer",data);
        
    }
    printf(CYAN"+----------------------+--------------------------------+\n"RESET);
}
//function definition
void read_tag(char*filename)
{
    FILE*fp=fopen(filename,"rb");
    if(fp==NULL)
    {
        printf(RED"Unable to open the files\n"RESET);
        return;
    }
    char id[4];
    fread(id,1,3,fp);
    id[3]='\0';
    printf("ID : %s\n",id);
    unsigned char version[2];
    fread(version,1,2,fp);
    printf("Version : 2.%d.%d\n",version[0],version[1]);
    printf("\n");
    printf(CYAN"+----------------------+--------------------------------+\n"RESET);
    printf(CYAN "|" RESET YELLOW" %-20s "RESET CYAN "|" RESET YELLOW " %-30s "RESET CYAN "|\n" RESET,"FIELD","VALUE");
    printf(CYAN"+----------------------+--------------------------------+\n"RESET); 
    fseek(fp,5,SEEK_CUR);
    read_frame(fp);
    read_frame(fp);
    read_frame(fp);
    read_frame(fp);
    read_frame(fp);
    read_frame(fp);
    fclose(fp);
        
    


}

