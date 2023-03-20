#include<stdio.h> 
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<fcntl.h> 
// #include<err.h> // На Windows не му харесва тази библиотека 

void manual_warning(char *message, char *also) {
    printf("\033[35mmanual-warning:\033[m \033[33m%s [\033[m\033[35m-%s\033[m\033[33m]\033[m", message, also); 
} 

int priv_strlen(char *str) {
    int i = 0; 
    while(str[i] != '\0') 
        i++; 

    return i; 
}

// char *int_to_string(int a) {
//     char *out = malloc(3 * sizeof(char)); 
//     if (a > 0 && a < 10) {
//         out[0] = itoa(a, out, 10);  
//         out[1] = '\0'; 
//     } 
//     switch (a) 
//     {
//     case 10: 
//         out[0] = "1"; 
//         out[1] = "0"; 
//         break;
    
//     default:
//         break;
//     }
// }

int get_score_of_student(char *file_student_answers, char *answers) {
    int fd_stud_ans = open(file_student_answers, O_RDONLY); 
    if (fd_stud_ans == -1) {
        close(fd_stud_ans); 
        printf("Error opening file for reading!\n"); 
        return 0; 
    }
    int fd_ans = open(answers, O_RDONLY); 
    if (fd_ans == -1) {
        close(fd_stud_ans); 
        close(fd_ans); 
        printf("Error opening file for reading!\n"); 
        return 0; 
    }

    uint8_t count = 0, grade = 0; 
    
    for(size_t i = 0; i < 25; i++) {
        char student_answer, correct_answer; 

        int read_status_fd_stud_answer = read(fd_stud_ans, &student_answer, 1); 
        if (read_status_fd_stud_answer == -1) {
            close(fd_stud_ans); 
            close(fd_ans); 
            // err(2, "Couldn't open file for reading"); 
            printf("Couldn't open file for reading!\n"); 
            return 0; 
        } 
        int lseek_status_one = lseek(fd_stud_ans, 1, SEEK_CUR); 
        if (lseek_status_one == -1) {
            close(fd_stud_ans); 
            close(fd_ans); 
            // err(3, "Couldn't use lseek"); 
            printf("Couldn't use lseek!\n"); 
            return 0; 
        }
        int read_status_fd_ans = read(fd_ans, &correct_answer, 1); 
        if (read_status_fd_ans == -1) {
            close(fd_stud_ans); 
            close(fd_ans); 
            // err(4, "Couldn't open file for reading"); 
            printf("Couldn't open file for reading!\n"); 
            return 0; 
        }
        int lseek_status_two = lseek(fd_ans, 1, SEEK_CUR); 
        if (lseek_status_two == -1) {
            close(fd_stud_ans); 
            close(fd_ans); 
            // err(5, "Couldn't use lseek"); 
            printf("Couldn't use lseek!\n"); 
            return 0; 
        }
        if (student_answer == correct_answer) 
            count++; 
    }

    if (count <= 12) {
        grade = 2; 
    } else if (count > 12 && count <= 15) {
        grade = 3; 
    } else if (count > 15 && count <= 18) {
        grade = 4; 
    } else if (count > 18 && count <= 21) {
        grade = 5; 
    } else if (count > 21 && count <= 25) {
        grade = 6; 
    }

    close(fd_stud_ans); 
    close(fd_ans); 

    return grade; 
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("\033[31mToo few arguments!\033[m\n"); 
        return 0; 
    } else if (argc > 3) {
        printf("\033[31mToo many arguments!\033[m\n"); 
        return 0; 
    }

    //printf("\033[30mThe directories in the input are expected to have '\033[m\033[31m/\033[m\033[30m'!"); 
    // printf("\033[35mmanual-warning:\033[m \033[33mThe directories in the input are expected to have '\033[m\033[31m/\033[m\033[30m\033[33m'! [\033[m\033[35m-Just-a-remainder\033[m\033[33m]\033[m ");
    manual_warning("The directories in the input are expected to have slash!", "Just-a-reminder"); 

    char *student_ans_dir = argv[1]; 
    char *correct_ans = argv[2]; 
    char *student_grade_dir = argv[3]; 

    char *student_ans = malloc((priv_strlen(student_ans_dir)) + (3 * sizeof(char))); 
    //char *correct_ans = malloc((priv_strlen(correct_ans_dir)) + (3 * sizeof(char))); 
    char *student_grade = malloc((priv_strlen(student_grade_dir)) + (3 * sizeof(char))); 

    for(size_t i = 0; i < 25; i++) {
        int file_number = 1; 

        sprintf(student_ans, "%s%d\0", student_ans_dir, file_number); 
        //sprintf(correct_ans, "%s%d", correct_ans_dir, file_number); 
        sprintf(student_grade, "%s%d\0", student_grade_dir, file_number); 

        int fd_student_grade = open(student_grade, O_WRONLY); 
        if (fd_student_grade == -1) {
            close(fd_student_grade); 
            printf("Error opening file for writing!\n");
        }

        uint8_t grade = get_score_of_student(student_ans, correct_ans); 
        int write_status = write(fd_student_grade, &grade, 1); 
        if (write_status == -1) {
            close(fd_student_grade); 
            printf("Couldn't write to file!\n"); 
            return 0; 
        }

        close(fd_student_grade);   
        file_number++;      
    }

    free(student_ans_dir); 
    //free(correct_ans_dir); 
    free(student_grade_dir); 
    free(student_ans); 
    free(correct_ans); 
    free(student_grade);  

    return 0; 
}
