/* written by client - calls client stub, xdr client, xdr xerver, server stub, server routine */

#include "avg.h"        /* header file generated by rpcgen */
#include <stdlib.h>


/* local routine client */
/* prototype can be whatever you want */
void averageprog_1( char* host, int argc, char *argv[] )
{
   CLIENT *clnt; /* client handle, rpc.h included in avg.h from rpcgen */
   int i;
   int strLength = 0;
   char *f, *dp;
   double  *result_1;
   char         *endptr;
   input_data  average_1_arg, *result_2; /* input_data rpc struct */

   average_1_arg.input_data.input_data_val = (char*) malloc(MAXAVGSIZE*sizeof(char));

   /* pointer to double, beginning of input data */
   dp = average_1_arg.input_data.input_data_val;

   /* set number of items */
   average_1_arg.input_data.input_data_len = argc - 2;

   for( i = 1; i <= (argc - 2); i++ ) {

	//get the inputted string
        f = argv[i+1];

	//set the inputted string to dp
        dp = f;

	     //set the current input_data_val to dp
	     average_1_arg.input_data.input_data_val = dp;
         
	     //find the length of the inputted string	
	     while(*dp != '\0') {

		  dp++;
	          strLength++;
             }
   }


   /*  clnt_create(host, program, version, protocol)
    * generic client create routine from rpc library * * program = AVERAGEPROG is the number 22855
    * version = AVERAGEVERS is 1
    * transfer protocol
    *
    * defined by application programmer in avg.x and  then
    * these definitions in turn are generated into avg.h
    * udp is of-course the user datagram protocol
    *
    * returns a client RPC handle
    */

   clnt = clnt_create( host, AVERAGEPROG, AVERAGEVERS, "udp" );

   /* check if error */
   if (clnt == NULL)
   {
      /*
       * rpc error library routine
       *  print a more descriptive error
       */

      clnt_pcreateerror( host );
      exit(1);
   }


   /* now call average routine 'just' like a local routine
    * but this will now go over network
    * average_1 is definined in the client stub
    * avg_clnt.c  that was generated by rpcgen
    * send in ptr to the parameters or args  in first field, and
    * client handle in second field (created in clnt_create )
    * average_1 ultimately calls clnt_call() macro see man rpc
    *  than calls the remote routine associated with the client handle
    * so AVERAGEPROG, VERSION
    */


      result_2 = average_1(&average_1_arg, clnt);

      if (result_2 == NULL) {
         clnt_perror(clnt, "call failed:");
      }

      clnt_destroy( clnt );
      printf( "Client print after receiving \n" );
      printf( "SERVER: ");

	  //get the input_data_value from resunt_2 that was returned and print char by char
          for (i = 0; i < strLength; i++) {

               printf("%c", *result_2->input_data.input_data_val);
	       result_2->input_data.input_data_val++;
    	  }

       printf("\n");
  }


/* here is main */
main( int argc, char* argv[] )
{
   char *host;

   /* check correct syntax */
   if( argc < 3 )
   {
    	printf( "usage: %s server_host value ...\n", argv[0]);
        exit(1);
   }

   if( argc > MAXAVGSIZE + 2 )
   {
    	printf("Two many input values\n");
        exit(2);
   }

   /* host name is in first parameter (after program name) */
   host = argv[1];
   averageprog_1( host, argc, argv);
}



