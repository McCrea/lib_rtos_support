/*
 * intertile_channel.c
 *
 *  Created on: Sep 24, 2019
 *      Author: mbruno
 */

#include "soc.h"

#include "xcore_c.h"

chanend xcore_freertos_channel_establish(
        chanend remote_tile_chanend,
        xcore_freertos_channel_direction_t direction)
{
    chanend local_c;

    chanend_alloc(&local_c);

    if (direction & xcore_freertos_channel_input) {
        s_chan_out_word(remote_tile_chanend, local_c);
        s_chan_out_ct_end(remote_tile_chanend);
    }

    if (direction & xcore_freertos_channel_output) {
        chanend remote_c;
        s_chan_in_word(remote_tile_chanend, (uint32_t *) &remote_c);
        s_chan_check_ct_end(remote_tile_chanend);
        chanend_set_dest(local_c, remote_c);
    }

    return local_c;
}