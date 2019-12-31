88c22_U33_WT2000_DANTE
{
	HAL_AudCodecWrite(audCodec,0x00, 0x055);
	DRIVER_DELAY(5);
	HAL_AudCodecWrite(audCodec,0x01, 0x0ED);
	HAL_AudCodecWrite(audCodec,0x02, 0x03F);
	HAL_AudCodecWrite(audCodec,0x03, 0x183);
	HAL_AudCodecWrite(audCodec,0x04, 0x014);
	HAL_AudCodecWrite(audCodec,0x06, 0x009);
	HAL_AudCodecWrite(audCodec,0x0A, 0x008);
	HAL_AudCodecWrite(audCodec,0x0B, 0x0FF);
	HAL_AudCodecWrite(audCodec,0x0C, 0x1FF);
	HAL_AudCodecWrite(audCodec,0x0E, 0x008);
	HAL_AudCodecWrite(audCodec,0x0F, 0x0FF);
	HAL_AudCodecWrite(audCodec,0x10, 0x1FF);
	HAL_AudCodecWrite(audCodec,0x2C, 0x033);
	HAL_AudCodecWrite(audCodec,0x2F, 0x050);
	HAL_AudCodecWrite(audCodec,0x30, 0x050);
	HAL_AudCodecWrite(audCodec,0x31, 0x002);
	HAL_AudCodecWrite(audCodec,0x38, 0x001);
	HAL_AudCodecWrite(audCodec,0x39, 0x001);
}

88c22_U37_DANTE
{
	HAL_AudCodecWrite(audCodec,0x00, 0x055);
	DRIVER_DELAY(5);
	HAL_AudCodecWrite(audCodec,0x01, 0x0AD);
	HAL_AudCodecWrite(audCodec,0x02, 0x03F);
	HAL_AudCodecWrite(audCodec,0x03, 0x103);
	HAL_AudCodecWrite(audCodec,0x04, 0x010);
	HAL_AudCodecWrite(audCodec,0x06, 0x008);
	HAL_AudCodecWrite(audCodec,0x0A, 0x008);
	HAL_AudCodecWrite(audCodec,0x0B, 0x1FF);
	HAL_AudCodecWrite(audCodec,0x0E, 0x008);
	HAL_AudCodecWrite(audCodec,0x0F, 0x1FF);
	HAL_AudCodecWrite(audCodec,0x2C, 0x003);
	HAL_AudCodecWrite(audCodec,0x2F, 0x050);
	HAL_AudCodecWrite(audCodec,0x30, 0x000);
	HAL_AudCodecWrite(audCodec,0x31, 0x002);
	HAL_AudCodecWrite(audCodec,0x38, 0x040);
	HAL_AudCodecWrite(audCodec,0x39, 0x008);
}


