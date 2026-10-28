/* Fuzz harness for udp/json-parser (JSON parser).
 *
 * This parser takes the length itself, so NO NUL terminator is needed.
 * Entry point:
 *   json_value *json_parse(const json_char *json, size_t length);
 *   void        json_value_free(json_value *);
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "json.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    /* TODO 1: json_value *v = json_parse((const json_char *)data, size);
     * TODO 2: if (v) json_value_free(v);
     * (no malloc/copy needed here — the parser takes a length)
     */
    (void)data; (void)size;
    return 0;
}
