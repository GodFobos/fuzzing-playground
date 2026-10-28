/* Fuzz harness for benhoyt/inih (INI parser).
 *
 * inih is a PUSH parser: it calls a handler callback for every key=value it
 * finds. So the harness must (a) provide that handler, (b) feed it the bytes.
 *
 * Entry point used:
 *   int ini_parse_string(const char* string, ini_handler handler, void* user);
 * Handler signature required by inih:
 *   int handler(void* user, const char* section, const char* name, const char* value);
 *   -> return 1 to continue parsing, 0 to stop.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"

/* TODO 1: write the handler.
 *   - match the signature above
 *   - mark the args unused: (void)user; ... 
 *   - return 1;
 */

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    /* TODO 2: make a NUL-terminated copy of (data, size):
     *         malloc(size + 1), memcpy, set last byte to '\0'
     *         (bail out with return 0 if malloc returns NULL)
     * TODO 3: ini_parse_string(copy, your_handler, NULL);
     * TODO 4: free(copy);
     */
    (void)data; (void)size;   /* delete this line once you use them */
    return 0;
}
