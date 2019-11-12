/*
	Interface to token generator
	OpenTokenFile attempts to open given file for extraction of tokens
	returns 0 if unable to open
	NextToken returns the next word in the file, with
	return value of 0 indicating end of file.
	It is up to the caller to clean up memory allocated for the token.
*/

int openTokenFile(const char[]);
char* nextToken();
