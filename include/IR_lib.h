/*
 * IR_lib.h
 *
 *  Created on: Jan 12, 2023
 *      Author: adevries
 */

#ifndef INCLUDE_IR_LIB_H_
#define INCLUDE_IR_LIB_H_

#include "device_protocol_structs.h"
#include "cmd_assoc_structs.h"

#include <stdint.h>
#include <stdbool.h>

const struct btn_assoc * get_command(uint16_t button_num);

int16_t handle_btn_assoc(struct btn_assoc const *container);
int16_t execute_command(const struct command *cmd, bool is_ditto);
inline void reset_prev_cmd(void);
int16_t format_sony20_command(uint8_t *output_buffer, uint16_t output_buffer_size,
                              const struct stream_char *cur_char,
                              const struct command *cmd, bool is_ditto);
int16_t format_NEC1_command(uint8_t *output_buffer, uint16_t output_buffer_size,
                           const struct stream_char *cur_char,
                           const struct command *cmd, bool is_ditto);
int16_t format_NEC2_command(uint8_t *output_buffer, uint16_t output_buffer_size,
                           const struct stream_char *cur_char,
                           const struct command *cmd, bool is_ditto);


#endif /* INCLUDE_IR_LIB_H_ */
