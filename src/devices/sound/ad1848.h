// license:BSD-3-Clause
// copyright-holders:Carl
#ifndef _AD1848_H_
#define _AD1848_H_

#include "sound/dac.h"

#define MCFG_AD1848_IRQ_CALLBACK(_cb) \
	devcb = &ad1848_device::set_irq_callback(*device, DEVCB_##_cb);

#define MCFG_AD1848_DRQ_CALLBACK(_cb) \
	devcb = &ad1848_device::set_drq_callback(*device, DEVCB_##_cb);

class ad1848_device : public device_t
{
public:
	ad1848_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);
	DECLARE_READ8_MEMBER(dack_r);
	DECLARE_WRITE8_MEMBER(dack_w);
	template<class _Object> static devcb_base &set_irq_callback(device_t &device, _Object object) { return downcast<ad1848_device &>(device).m_irq_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_drq_callback(device_t &device, _Object object) { return downcast<ad1848_device &>(device).m_drq_cb.set_callback(object); }
	virtual machine_config_constructor device_mconfig_additions() const override;
protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
private:
	union {
		struct {
			uint8_t linp;
			uint8_t rinp;
			uint8_t laux1;
			uint8_t raux1;
			uint8_t laux2;
			uint8_t raux2;
			uint8_t lout;
			uint8_t rout;
			uint8_t dform;
			uint8_t iface;
			uint8_t pinc;
			uint8_t init;
			uint8_t misc;
			uint8_t mix;
			uint8_t ubase;
			uint8_t lbase;
		};
		uint8_t idx[15];
	} m_regs;
	uint8_t m_addr;
	uint8_t m_stat;
	uint16_t m_count;
	uint32_t m_samples;
	uint8_t m_sam_cnt;
	bool m_play, m_mce, m_trd, m_irq;
	devcb_write_line m_irq_cb;
	devcb_write_line m_drq_cb;
	required_device<dac_word_interface> m_ldac;
	required_device<dac_word_interface> m_rdac;
	emu_timer *m_timer;
};

extern const device_type AD1848;

#endif
