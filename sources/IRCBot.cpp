#include "IRCBot.hpp"
#include "KickCmd.hpp"

IRCBot::IRCBot(Context* context, std::string message, std::string channel_name) {
	Request* req = context->request;
	sender = context->users->find(req->get_fd())->second;
	channel = context->channels->find(channel_name)->second;
	data = message;
	bot = context->users->find(context->server_info->fd)->second;
	ch_name = channel_name;
	this->context = context;
}

bool IRCBot::is_valid() {
	if (is_insult()) {
		type = INSULT;
		return false;
	}
	return true;
}

bool IRCBot::is_insult() {
	std::string insults[5] = {"retard", "fuck", "mklkh", "7mar", "hmar"};
	for (int i = 0; i < 5; i++) {
		if (data.find(insults[i]) != std::string::npos)
			return true;
	}
	return false;
}

void IRCBot::take_action() {
	if (type == INSULT) {
		Request* req = new Request(context->server_info->fd);
		req->set_cmd("KICK");
		req->set_options(ch_name + " " + sender->get_nickname());
		context->requests->push(req);
	}
}