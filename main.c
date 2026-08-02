/*
Name : Ganavi VR
Project: MP3 tag reader and editor
Reg no: INT26001B_132
Description:The MP3 Tag Reader and Editor is a C-based application developed to read and modify metadata stored in MP3 audio files. MP3 files contain ID3 tags that store information such as the song title, artist name, album name, year, composer, and content type. This project allows users to view and edit these metadata fields directly from the command line without affecting the actual audio content of the file.
The application supports the ID3v2.3 standard and performs file operations at the binary level. It reads frame headers, extracts metadata information, and displays it in a structured tabular format. The editing feature allows users to update selected tags by creating a temporary MP3 file, modifying the required frame data, and replacing the original file while preserving the remaining metadata and audio data.
The project demonstrates concepts such as file handling, command-line argument processing, structures, modular programming, dynamic memory allocation, and binary data manipulation in C.
Date:10/06/2026
*/
#include"common.h"
#include"read.h"
#include"edit.h"
int main(int argc,char*argv[])
{
    if(argc==3)
    {
        if(strcmp(argv[1],"-v")!=0)
        {
            printf(RED"Invalid option\n"RESET);
            return 1;

        }
         //printf("USAGE: ./a.out -v song.mp3\n");
         // return 1;
        char*ext=strrchr(argv[2],'.');
        if(ext==NULL||strcmp(ext,".mp3")!=0)
        {
          printf(RED"Not an MP3 file\n"RESET);
          return 1;
        }
       // printf("All validations successfull\n");
       read_tag(argv[2]);
    }
    else if(argc==5)
    {
        if(strcmp(argv[1],"-e")!=0)
        {
            printf(RED"Invalid edit option\n"RESET);
            return 1;
        }

        //valid frame checking
        char frame[5];
        if(strcmp(argv[2],"-t")==0)
        {
            strcpy(frame,"TIT2");
        }
        else if(strcmp(argv[2],"-a")==0)
        {
            strcpy(frame,"TPE1");
        }
        else if(strcmp(argv[2],"-A")==0)
        {
            strcpy(frame,"TALB");
        }
        else if(strcmp(argv[2],"-y")==0)
        {
            strcpy(frame,"TYER");
        }
        else if(strcmp(argv[2],"-c")==0)
        {
            strcpy(frame,"TCOM");
        }
        else if(strcmp(argv[2],"-C")==0)
        {
            strcpy(frame,"TCON");
        }
        else
        {
            printf(RED"Invalid tag name\n"RESET);
            return 1;
        }

        //checking for extension of the song file
        char*ext=strrchr(argv[4],'.');
        if(ext==NULL || strcmp(ext,".mp3")!=0)
        {
            printf(RED"Not an mp3 file\n"RESET);
            return 1;
        }
        edit_tag(argv[4],frame,argv[3]);
    }
    else
    {
        printf(GREEN"usage:\n"RESET);
        printf(GREEN"./a.out -v song.mp3\n"RESET);
        printf(GREEN"./a.out -e FRAME \"Data\" song.mp3\n"RESET);
    }
    return 0;
}
    
