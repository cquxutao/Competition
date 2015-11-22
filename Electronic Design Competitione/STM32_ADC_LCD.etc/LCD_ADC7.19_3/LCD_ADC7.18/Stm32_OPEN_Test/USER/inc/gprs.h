#ifndef __GPRS_H
#define __GPRS_H

u16 GPRS_RecvData(u8 *buf,const u32 timeout);
void GPRS_SendData(u8 *buf,u16 len);
u8 gprs_init_check(void);
void gprs_pkey_down(void);
void delete_sms(u8 addr);
void send_sms(u8 *tele,u8 *message);
void send_pdu_sms(u8 *tele,u8 *message);
void send_sms_elec_para(char *tel,u8 type);
void read_sms_process(void);
void read_sms(u8 addr,u8 *pbuf);
void set_mms_url(void);
void active_mms(void);
void send_mms(u8 *tele,u8 *title,u8 *message,u8 *photo,u32 photo_len);
void send_mail(u8 *mailbox,u8 *title,u8 *message,u8 *photo,u32 photo_len);
#endif