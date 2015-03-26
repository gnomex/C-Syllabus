#include "encrypt.h"


// read_from_file -> filename
//   a buffer
//   a file
//   approx quantity of chars (sizeof(file) / sizeof(char))

//   while the file not end and current < approx (DEAL with EOF)

//     append to buffer ( DEAL with buffers sizes)

//     // async!!!!!!!
//     if buffer full
//         process
//         crypt
//         async write

//         no errors -> flush buffer
//         errors -> fuuu

//     done
// kill -9

// crypt -> buffer, salt
//   magic

// decrypt -> buffer, salt
//   magic

// reverse -> buffer


int main(int argc, char const *argv[])  {
  return 0;
}
