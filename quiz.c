#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTIONS 10
#define MAX_LENGTH 256

// Define the Question structure
typedef struct {
    char question_text[MAX_LENGTH];
    char correct_answer[MAX_LENGTH];
} Question;

// Function to read questions and answers from files
int read_questions_answers(const char *question_file, const char *answer_file, Question questions[MAX_QUESTIONS]) {
    FILE *q_file = fopen(question_file, "r");
    FILE *a_file = fopen(answer_file, "r");
    
    if (!q_file || !a_file) {
        printf("Unable to open question or answer file.\n");
        if (q_file) fclose(q_file);
        if (a_file) fclose(a_file);
        return 0;
    }
    
    int count = 0;
    while (count < MAX_QUESTIONS) {
        // Read question
        if (fgets(questions[count].question_text, MAX_LENGTH, q_file) == NULL) break;
        // Remove newline character from question
        size_t len = strlen(questions[count].question_text);
        if (len > 0 && questions[count].question_text[len - 1] == '\n') {
            questions[count].question_text[len - 1] = '\0';
        }
        
        // Read answer
        if (fgets(questions[count].correct_answer, MAX_LENGTH, a_file) == NULL) break;
        // Remove newline character from answer
        len = strlen(questions[count].correct_answer);
        if (len > 0 && questions[count].correct_answer[len - 1] == '\n') {
            questions[count].correct_answer[len - 1] = '\0';
        }
        
        count++;
    }
    
    fclose(q_file);
    fclose(a_file);
    return count;
}

// Main function
int main() {
    Question questions[MAX_QUESTIONS];
    
    // Display menu options
    printf("Menu:\n");
    printf("1. Start the quiz\n");
    printf("2. Exit the program\n");
    
    // Get user's choice
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    // Start the quiz if the user chooses option 1
    if (choice == 1) {
        // Read questions and answers from files
        int question_count = read_questions_answers("quizquestion.txt", "quizanswer.txt", questions);
        
        if (question_count == 0) {
            printf("Failed to read questions and answers.\n");
            return 1;
        }
        
        // Ask the user for their details
        char name[MAX_LENGTH];
        char phone_number[MAX_LENGTH];
        int age;
        
        printf("Enter your name: ");
        scanf(" %[^\n]s", name);
        
        printf("Enter your phone number: ");
        scanf("%s", phone_number);
        
        printf("Enter your age: ");
        scanf("%d", &age);
        
        printf("\nThank you, %s. Let's begin the quiz!\n\n", name);
        
        // Initialize score
        int score = 0;
        
        // Quiz loop
        for (int i = 0; i < question_count; i++) {
            printf("Question %d: %s\n", i + 1, questions[i].question_text);
            
            // Get the user's answer
            char user_answer[MAX_LENGTH];
            printf("Your answer: ");
            scanf(" %[^\n]s", user_answer); // Use %[^\n]s to read a line of text
            
            // Compare user's answer with correct answer
            if (strcmp(user_answer, questions[i].correct_answer) == 0) {
                printf("Correct!\n");
                score++;
            } else {
                printf("Wrong! The correct answer is: %s\n", questions[i].correct_answer);
            }
            printf("\n");
        }
        
        // Display the final score
        printf("Quiz over! Your final score is: %d out of %d\n", score, question_count);
    } else {
        // Exit the program
        printf("Exiting the program.\n");
        return 0;
    }

    return 0;
}

