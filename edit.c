#include"common.h"
#include"edit.h"

//function definition
void edit_tag(char*filename,char*frame_name,char*new_data)
{
    FILE*fp=fopen(filename,"rb");
    if(fp==NULL)
    {
        printf(RED"Unable to open file\n"RESET);
        return;
    }
    FILE*temp=fopen("temporary.mp3","wb");
    if(temp==NULL)
    {
        printf(RED"Unable to open temp file\n"RESET);
        fclose(fp);
        return;
    }

    //copying the header bytes

    char header[10];
    fread(header, 1, 10,fp);
    fwrite(header, 1, 10,temp);
    int i;
    for(i=0;i<6;i++)
    {
        char frame_id[5];
        fread(frame_id,1,4,fp);
        frame_id[4]='\0';

        if(frame_id[0]=='\0')
        {
            break;
        }
        fwrite(frame_id,1,4,temp);

        //reading old frames size

        unsigned char size[4];
        fread(size,1,4,fp);
        int old_size = get_size(size);

        if(old_size<=0)
        {
            break;
        }

        //reading flags

        char flags[2];
        fread(flags, 1, 2,fp);

        //reading encoding byte

        char encoding;
        fread(&encoding, 1, 1, fp);

        //reading old data

        char*old_data=malloc(old_size);
        
        fread(old_data,1,old_size-1,fp);
        old_data[old_size-1]='\0';

        //if frame matches
        if(strcmp(frame_id,frame_name)==0)
        {
            int new_size=strlen(new_data)+1;
            unsigned char new_size_bytes[4];
            convert_size(new_size,new_size_bytes);
            //fwrite(size,1,4,temp);

            fwrite(new_size_bytes,1,4,temp);
            fwrite(flags,1,2,temp);
            //char encoding;
            fwrite(&encoding,1,1,temp);
            fwrite(new_data,1,strlen(new_data),temp);
            

        }
        else
        {
            fwrite(size,1,4,temp);
            fwrite(flags,1,2,temp);
            fwrite(&encoding,1,1,temp);
            fwrite(old_data,1,old_size-1,temp);
        }
        free(old_data);
    }
    //copying remaing audio

    char ch;
    while(fread(&ch,1,1,fp))
    {
        fwrite(&ch,1,1,temp);
    }
    fclose(fp);
    fclose(temp);

    //replacing old file

    remove(filename);
    rename("temporary.mp3",filename);
    printf(GREEN"Tag edited succcessfully\n"RESET);
}