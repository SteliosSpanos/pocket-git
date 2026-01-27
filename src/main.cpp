#include <cstdio>
#include "utils/string_utils.h"
#include "utils/compression.h"
#include "utils/file_utils.h"
#include "utils/hash_utils.h"

int main()
{
	std::string hash = Sha256HashHex("hello");
	printf("SHA256('hello'): %s\n", hash.c_str());

	std::string original = "hello world hello world hello world";
	std::string compressed = ZlibCompress(original);
	std::string decompressed = ZlibDecompress(compressed);

	printf("Compression: %zu -> %zu bytes\n", original.size(), compressed.size());
	printf("Roundtrip OK: %s\n", (original == decompressed) ? "yes" : "no");

	return 0;
}
