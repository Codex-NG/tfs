//////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//////////////////////////////////////////////////////////////////////
#include "otpch.h"

#include "protocolhttp.h"
#include "resources.h"

#include "outputmessage.h"
#include "connection.h"

#include "configmanager.h"
#include "tools.h"
#include "iologindata.h"
#include "ioban.h"
#include <iomanip>
#include "game.h"

#ifdef __ENABLE_SERVER_DIAGNOSTIC__
uint32_t ProtocolHTTP::protocolHTTPCount = 0;
#endif

void ProtocolHTTP::deleteProtocolTask()
{
#ifdef __DEBUG_NET_DETAIL__
	std::cout << "Deleting ProtocolHTTP" << std::endl;
#endif
	Protocol::deleteProtocolTask();
}

void ProtocolHTTP::disconnectClient()
{
	getConnection()->close();
}

bool ProtocolHTTP::parseFirstPacket(NetworkMessage& msg)
{
	uint32_t clientIP = getConnection()->getIP();
	std::string getRequest = msg.GetString();
	std::cout << getRequest << std::endl;

	if (ConnectionManager::getInstance()->isDisabled(clientIP, protocolId)) {
		disconnectClient();
		return false;
	}

	if (IOBan::getInstance()->isIpBanished(clientIP)) {
		disconnectClient();
		return false;
	}

	ConnectionManager::getInstance()->addAttempt(clientIP, protocolId, true);
	if (OutputMessage_ptr output = OutputMessagePool::getInstance()->getOutputMessage(this, false)) {
		TRACK_MESSAGE(output);

		output->AddString("HTTP/1.1 200 OK");
		output->AddString("Date: Fri, 27 Mar 2009 17:28.13 GMT\r\n");
		output->AddString("Server: The Forgotten Server httpd/0.4\r\n");
		output->AddString("Content-Location: filename.html\r\n");
		//Vary: negotiate\r\n
		//TCN: choice\r\n
		output->AddString("Last-Modified: Fri, 27 Mar 2009 17:28.13 GMT\r\n");
		output->AddString("Accept-Ranges: bytes\r\n");
		output->AddString("Content-Length: 1234\r\n");
		output->AddString("Expires: Fri, 27 Mar 2009 17:28.13 GMT\r\n");
		output->AddString("Connection: close\r\n");
		output->AddString("Content-Type: text/html qs=0.7\r\n");
		output->AddString("\r\n");
		output->AddString("<html><head><title>The Forgotten Server httpd</title></head><body>It works (apache ripoff ;D)!</body></html>");

		OutputMessagePool::getInstance()->send(output);
	}

	getConnection()->close();
	return true;
}
