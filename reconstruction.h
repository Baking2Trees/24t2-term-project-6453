#ifndef RECONSTRUCTION_H
#define RECONSTRUCTION_H

// Takes in the transfer file which contains the missing block information and adds the new data to filename
// Note: Transfer file must already be decrypted
void reconstruct(char *transferfile, char *filename);

#endif // RECONSTRUCTION_H