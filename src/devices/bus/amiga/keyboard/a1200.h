// license:BSD-3-Clause
// copyright-holders: Vas Crabb
/***************************************************************************

    Amiga 1200 Keyboard

 ***************************************************************************/

#ifndef DEVICES_BUS_AMIGA_KEYBOARD_A1200_H
#define DEVICES_BUS_AMIGA_KEYBOARD_A1200_H

#pragma once

#include "keyboard.h"


//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

extern device_type const A1200_KBD;


namespace bus { namespace amiga { namespace keyboard {

//**************************************************************************
//  TYPE DECLARATIONS
//**************************************************************************

// ======================> a1200_kbd_device

class a1200_kbd_device : public device_t, public device_amiga_keyboard_interface
{
public:
	// construction/destruction
	a1200_kbd_device(machine_config const &mconfig, char const *tag, device_t *owner, uint32_t clock);

	// from host
	virtual DECLARE_WRITE_LINE_MEMBER(kdat_w) override;

	// MPU I/O
	DECLARE_READ8_MEMBER(mpu_portb_r);
	DECLARE_WRITE8_MEMBER(mpu_porta_w);
	DECLARE_WRITE8_MEMBER(mpu_portb_w);
	DECLARE_WRITE8_MEMBER(mpu_portc_w);
	DECLARE_WRITE_LINE_MEMBER(mpu_tcmp);

protected:
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual machine_config_constructor device_mconfig_additions() const override;
	virtual ioport_constructor device_input_ports() const override;

	virtual void device_start() override;
	virtual void device_reset() override;

private:
	required_ioport_array<15>   m_rows;
	required_device<cpu_device> m_mpu;

	u16                         m_row_drive;
	bool                        m_host_kdat, m_mpu_kdat;
};

} } } // namespace bus::amiga::keyboard

#endif // DEVICES_BUS_AMIGA_KEYBOARD_A1200_H
