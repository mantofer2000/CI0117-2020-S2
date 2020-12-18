#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <omp.h>
#include "mpi.h"

using namespace std;

void initArray(int *array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array[i] = 0;
    }
}

int main(int argc, char *argv[])
{

    int my_id, num_processes;
    int message_received, message_sent;
    MPI_Status status;
    string sequence;
    int sequence_count_local[26];
    int sequence_count_global[26];

    initArray(sequence_count_local, 26);
    initArray(sequence_count_global, 26);

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    if (my_id == 0)
    {
        if (argc < 2)
        {
            cout << "Invalid number of params." << endl;
            return 1;
        }

        ifstream file(argv[1]);

        if (file.is_open())
        {
            getline(file, sequence);
            file.close();
        }
        else
        {
            cout << "Unable to open file" << argv[1] << endl;
            return 1;
        }
    }

    char *sequence_segment;
    int sequence_size = sequence.length();

    MPI_Bcast(&sequence_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int segment_size = floor((float)sequence_size / num_processes);

    if (segment_size < 1)
    {
        if (my_id == 0)
        {
            cout << "Too many processes for this sequence (size=" << sequence_size << ")" << endl;
        }
        return 1;
    }

    sequence_segment = new char[segment_size];

	double duration = MPI_Wtime();

    MPI_Scatter(&sequence[0], segment_size, MPI_CHAR, sequence_segment, segment_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    int index;
    for (int i = 0; i < segment_size; ++i)
    {
        index = sequence_segment[i] - 'a';
        if (index < 26 && index >= 0)
        {
            sequence_count_local[index]++;
        }
    }

    if (my_id == 0) // If I am process 0, let's check if we need to process any remaining characters
    {
        int remaining = sequence_size % segment_size;
        for (int i = sequence_size - 1; i >= (sequence_size - remaining); --i)
        {
            index = sequence[i] - 'a';
            if (index < 26 && index >= 0)
            {
                sequence_count_local[index]++;
            }
        }
    }

    MPI_Reduce(sequence_count_local, sequence_count_global, 26, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	duration = MPI_Wtime() - duration;

    if (my_id == 0)
    {

        cout << "Sequence size: " << sequence_size << ". Duration: "  << duration <<  endl;

        cout << "Sequence occurrences:";

        for (int j = 0; j < 26; ++j)
        {
            if (sequence_count_global[j] > 0)
            {
                cout << " " << (char)('a' + j) << "=" << sequence_count_global[j];
            }
        }
        cout << endl;
    }

    MPI_Finalize();

    delete[] sequence_segment;

    return 0;
}
