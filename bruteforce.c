#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <time.h>
#include <omp.h>


void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}



int main(void)

{


  /* Set up the key and iv. Do I need to say to not hard code these in a
   * real application? :-)
   */

  /* A 256 bit key */
  unsigned char *key = (unsigned char *)"newto###########";

  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x02\x05\x07";

  /* Message to be encrypted */
  unsigned char *plaintext =
                (unsigned char *)"What makes you who you are is the continues desire for success";

  /* Buffer for ciphertext. Ensure the buffer is long enough for the
   * ciphertext which may be longer than the plaintext, dependant on the
   * algorithm and mode
   */
  unsigned char ciphertext[128];
  unsigned char ciphertext2[128];
  double start_t, end_t;
  start_t = omp_get_wtime();








  /* Encrypt the plaintext */
  encrypt (plaintext, strlen ((char *)plaintext), key, iv, ciphertext);

  /* Do something useful with the ciphertext here */
  printf("Ciphertext is:\n");
  BIO_dump_fp (stdout, (const char *)ciphertext, 16);

  char pbuffer[1024];
  char password[17]="################";
  char alphabet[] = "aweontaaaaaaaaaa"; //awneotaaaaaaaaaa


  for(int i = 0; i < 16; i++)
  {
  	password[0] = alphabet [i];

  	for(int j = 0; j < 16; j++)
  	{
  		password[1] =alphabet [j];

  		for(int k = 0; k < 16; k++)
  		{
  			password[2] = alphabet [k];

  			for(int l = 0; l < 16; l++)
  			{
  			password[3] = alphabet [l];

                         for(int m = 0; m < 16; m++)
                           {
                                password[4] = alphabet [m];


          encrypt (plaintext, strlen ((char *)plaintext), password, iv, ciphertext2);

       if (strncmp(ciphertext,ciphertext2, 16) == 0){
          printf("\n%s",password);
          printf("  Key was successfully derived\n ");
          end_t = omp_get_wtime();
          printf ("\nCode start Time = %f\n", start_t);
          printf ("\nCode end Time = %f\n", end_t);
          printf ("\nCode Run Time = %f\n", end_t - start_t);
          exit(0);

       }

          printf("\n%s",password);
  }
    }
      }
        }
}
  return 0;
}
