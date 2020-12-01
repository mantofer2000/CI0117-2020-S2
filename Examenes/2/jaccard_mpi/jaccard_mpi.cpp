#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{

    string test_vector, test_text, matrix_row, text_row, most_similar_text, useless;
    int my_id, num_processes, array_size, message_sent, message_received;

    MPI_Init(&argc, &argv);
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    
    if (argc < 5)
    {
        cout << "Invalid number of params. Usage:" << endl;
        cout << "jaccard_similarity TEXT_FILE MATRIX_FILE" << endl;
        return 1;
    }

    ifstream text_file(argv[3]);

    if (!text_file.is_open())
    {
        cout << "Unable to open text file: " << argv[3] << endl;
        return 1;
    }

    ifstream matrix_file(argv[4]);

    if (!matrix_file.is_open())
    {
        cout << "Unable to open matrix file" << argv[4] << endl;
        text_file.close();
        return 1;
    }

    array_size = num_processes;
    double * array_results = new double [num_processes];

    // The first line is expected to be the text to be evaluated against the rest.
    getline(matrix_file, test_vector); // Get the vector representation of the text to be evaluated
    getline(text_file, test_text); // Get the text to be evaluated

    double words_union, words_intersection, jaccard_similarity, max_jaccard_similarity;;
    max_jaccard_similarity = -1.0;
    int i, j, k;
    j = 0;
    k = my_id;

    while (getline(matrix_file, matrix_row) && getline(text_file, text_row)) {
        words_union = words_intersection = 0.0;
        
        if(j == k){
                for (i = 0; i < matrix_row.length(); ++i) {
                if (matrix_row[i] == '1' || test_vector[i] == '1') { // If the word is present in any of the texts being compared, sum up to Union
                    ++words_union;
                }
                if (matrix_row[i] == '1' && test_vector[i] == '1') { // If the word is present in both texts, then sum up to Intersection
                    ++words_intersection;
                }
            }
            
            jaccard_similarity = words_intersection / words_union; // Calculate Jaccard similarity score
                

            if (jaccard_similarity > max_jaccard_similarity) { // Update highest Jaccard score if it is greater than the previous one
                max_jaccard_similarity = jaccard_similarity;
                most_similar_text = text_row;
            }
            k+= num_processes;
        }
        j++;
    }
    
    matrix_file.close();
    if(!my_id) {
        cout << "\nEvaluated text: \n\"" << test_text << "\"" << endl;
    }
    

    MPI_Allgather(&max_jaccard_similarity, 1, MPI_DOUBLE, array_results, 1, MPI_DOUBLE, MPI_COMM_WORLD);

    bool ok = true;
    for (int i = 0; i < array_size; i++) {
        if (array_results[i] > max_jaccard_similarity){
            ok = false;
            max_jaccard_similarity = array_results[i];
        }
    }


    if (my_id != 0) {
        MPI_Recv(&message_received, 1 /* count*/, MPI_INT, my_id - 1 /*source*/, 123 /*message id*/, MPI_COMM_WORLD, &status);
    }

    if (ok) {
        cout << "\nMost similar text: \n\"" << most_similar_text << "\"" << endl;
    }

    if (my_id == num_processes - 1)
        printf("\nJaccard similarity score: %.6f\n", max_jaccard_similarity);


	if ( my_id < num_processes - 1 ) {
        MPI_Send(&message_sent, 1 /*count*/, MPI_INT, my_id + 1 /*dest*/, 123 /*message id*/, MPI_COMM_WORLD);
    }

    text_file.close();

    delete[] array_results; 

    
    MPI_Finalize();

    return 0;
}