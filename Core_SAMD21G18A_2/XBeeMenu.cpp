#include "XBeeMenu.h"
//











//void sendAtCommand()
//{
//	int i10;
//	Serial.println("\nSending command sendAtCommand to the XBee");
//	xbee.send(atRequest);
//
//	if (xbee.readPacket(5000)) // подождите до 5 секунд для ответа состояния
//	{
//		if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE) // Должна быть команда отклика AT
//		{
//			xbee.getResponse().getAtCommandResponse(atResponse);
//
//			if (atResponse.isOk())
//			{
//				Serial.print("Command [");
//				Serial.print(atResponse.getCommand()[0]);
//				Serial.print(atResponse.getCommand()[1]);
//				Serial.println("] was successful!");
//
//				if (atResponse.getValueLength() > 0)
//				{
//					Len_XBee = atResponse.getValueLength();
//					Serial.print("\nCommand value length is - ");
//					Serial.println(atResponse.getValueLength(), DEC);
//					Serial.print("Command value: ");
//					int i11 = Len_XBee - 1;
//					info_XBee_data1[0] = 0;
//					info_XBee_data1[1] = 0;
//					info_XBee_data1[2] = 0;
//					info_XBee_data1[3] = 0;
//
//					for (i10 = 0; i10 < atResponse.getValueLength(); i10++)
//					{
//						info_XBee_data[i10] = atResponse.getValue()[i10];
//						Serial.print(info_XBee_data[i10], HEX);
//						Serial.print(" ");
//						info_XBee_data1[i11] = info_XBee_data[i10];
//						i11--;
//					}
//					Serial.println("");
//				}
//			}
//			else
//			{
//				Serial.print("Command return error code: ");
//				Serial.println(atResponse.getStatus(), HEX);
//			}
//		}
//		else
//		{
//			Serial.print("Expected AT response but got ");
//			Serial.println(xbee.getResponse().getApiId(), HEX);
//		}
//	}
//	else
//	{
//		if (xbee.getResponse().isError())             // at command failed
//		{
//			Serial.print("Error reading packet.  Error code: ");
//			Serial.println(xbee.getResponse().getErrorCode());
//		}
//		else
//		{
//			Serial.println("No response from radio1");
//		}
//	}
//	delay(100);
//}
//void sendAtCommand_ar()
//{
//	int i10;
//
//	Serial.println("\nSending command sendAtCommand_ar to the XBee");
//	xbee.send(arRequestMod);      // send the command
//
//								  // wait up to 5 seconds for the status response
//	if (xbee.readPacket(5000))
//	{
//
//		// should be an AT command response
//		if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE)
//		{
//			xbee.getResponse().getAtCommandResponse(atResponse);
//
//			if (atResponse.isOk())
//			{
//
//				//myGLCD.setColor(255 , 0, 0);
//
//				//	Serial.print("Command [");
//				//	Serial.print(atResponse.getCommand()[0]);
//				//	Serial.print(atResponse.getCommand()[1]);
//				//	Serial.println("] was successful!");
//
//				if (atResponse.getValueLength() > 0)
//				{
//					Len_XBee = atResponse.getValueLength();
//					//  Serial.print("Command value length is ");
//					//  Serial.println(atResponse.getValueLength(), DEC);
//					//  Serial.print("Command value: ");
//					int i11 = Len_XBee - 1;
//					info_XBee_data1[0] = 0;
//					info_XBee_data1[1] = 0;
//					info_XBee_data1[2] = 0;
//					info_XBee_data1[3] = 0;
//
//					for (i10 = 0; i10 < atResponse.getValueLength(); i10++)
//					{
//						info_XBee_data[i10] = atResponse.getValue()[i10];
//						Serial.print(info_XBee_data[i10], HEX);
//						info_XBee_data1[i11] = info_XBee_data[i10];
//						i11--;
//					}
//
//					// Serial.println("");
//				}
//			}
//			else
//			{
//				Serial.print("Command return error code: ");
//				Serial.println(atResponse.getStatus(), HEX);
//
//				//myGLCD.setColor(255, 0, 0);
//				//myGLCD.fillRoundRect(278, 92, 318, 132);
//				//myGLCD.setColor(255, 255, 255);
//				//myGLCD.drawRoundRect(278, 92, 318, 132);
//				//myGLCD.setBackColor(0, 0, 0);
//				//delay(200);
//				////XBee_alarm();
//				//delay(1000);
//				//myGLCD.setColor(0, 0, 0);
//				//myGLCD.fillRoundRect(278, 92, 318, 132);
//				//myGLCD.setColor(0, 0, 0);
//				//myGLCD.drawRoundRect(278, 92, 318, 132);
//				//	mcp_Out1.digitalWrite(Beep, LOW);                    // 
//				delay(300);
//			}
//		}
//		else
//		{
//			Serial.print("Expected AT response but got ");
//			Serial.println(xbee.getResponse().getApiId(), HEX);
//		}
//	}
//	else
//	{
//		// at command failed
//		if (xbee.getResponse().isError())
//		{
//			Serial.print("Error reading packet.  Error code: ");
//			Serial.println(xbee.getResponse().getErrorCode());
//		}
//		else
//		{
//			Serial.println("No response from radio2");
//		}
//	}
//}
//void sendRemoteAtCommand()
//{
//	Serial.println("\nSending command sendRemoteAtCommand to the XBee");
//	xbee.send(remoteAtRequest);
//
//	// wait up to 5 seconds for the status response
//	if (xbee.readPacket(5000))
//	{
//		// got a response!
//
//		// should be an AT command response
//		if (xbee.getResponse().getApiId() == REMOTE_AT_COMMAND_RESPONSE)
//		{
//			xbee.getResponse().getRemoteAtCommandResponse(remoteAtResponse);
//
//			if (remoteAtResponse.isOk()) {
//				Serial.print("Command [");
//				Serial.print(remoteAtResponse.getCommand()[0]);
//				Serial.print(remoteAtResponse.getCommand()[1]);
//				Serial.println("] was successful!");
//
//				if (remoteAtResponse.getValueLength() > 0) {
//					Serial.print("Command value length is ");
//					Serial.println(remoteAtResponse.getValueLength(), DEC);
//
//					Serial.print("Command value: ");
//
//					for (int i = 0; i < remoteAtResponse.getValueLength(); i++) {
//						Serial.print(remoteAtResponse.getValue()[i], HEX);
//						Serial.print(" ");
//					}
//
//					Serial.println("");
//				}
//			}
//			else {
//				Serial.print("Command returned error code: ");
//				Serial.println(remoteAtResponse.getStatus(), HEX);
//			}
//		}
//		else
//		{
//			Serial.print("Expected Remote AT response but got ");
//			Serial.print(xbee.getResponse().getApiId(), HEX);
//		}
//	}
//	else if (xbee.getResponse().isError())
//	{
//		Serial.print("Error reading packet.  Error code: ");
//		Serial.println(xbee.getResponse().getErrorCode());
//	}
//	else
//	{
//		Serial.print("No response from radio3");
//	}
//}
//void testRemoteAtCommand()
//{
//	// sendRemoteAtCommand();
//
//	// Теперь повторно тот же объект для команды DIO0
//	remoteAtRequest.setCommand(IDCmd);
//	remoteAtRequest.setCommandValue(IDValue);
//	remoteAtRequest.setCommandValueLength(sizeof(IDValue));
//
//	sendRemoteAtCommand();
//
//	// it's a good idea to clear the set value so that the object can be reused for a query
//	//это хорошая идея, чтобы очистить установленное значение, чтобы объект можно повторно использовать для запроса 
//	remoteAtRequest.clearCommandValue();
//
//	// we're done
//	// while (1) {};
//}
//void test_arRequestMod()
//{
//	arRequestMod.setCommand(command);
//	arRequestMod.setCommandValue(commandValue);
//	arRequestMod.setCommandValueLength(commandValueLength);
//	sendAtCommand_ar();
//	delay(250);
//	atRequest.setCommand(WRCmd);
//	sendAtCommand();
//	delay(250);
//	atRequest.setCommand(assocCmd);
//	sendAtCommand();
//	arRequestMod.clearCommandValue();
//}
//
//
