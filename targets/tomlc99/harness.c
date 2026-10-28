/* Fuzz harness for cktan/tomlc99 (TOML parser).
 *
 * tomlc99 returns a tree; you free it with toml_free.
 * Entry point:
 *   toml_table_t *toml_parse(char *conf, char *errbuf, int errbufsz);
 *   void          toml_free(toml_table_t *tab);
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "toml.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    /* TODO 1: NUL-terminated copy of (data, size)
     * TODO 2: char errbuf[256];
     * TODO 3: toml_table_t *tab = toml_parse(copy, errbuf, sizeof(errbuf));
     * TODO 4: if (tab) toml_free(tab);
     * TODO 5: free(copy);
     */
    (void)data; (void)size;
    return 0;
}
