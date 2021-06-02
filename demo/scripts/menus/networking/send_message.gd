extends PanelContainer

onready var peer_id_line_edit := $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/PeerID
onready var channel_id_line_edit := $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/ChannelID
onready var message_line_edit := $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/Message
onready var result_line_edit := $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit


func _on_send_button_down():
	var peer_id := int(peer_id_line_edit.text)
	var channel_id := int(channel_id_line_edit.text)
	var message: PoolByteArray = message_line_edit.text.to_utf8()

	var result: int = DiscordManager.networking.send_message(peer_id, channel_id, message)

	result_line_edit.text = DiscordManager.enum_to_string(Discord.Result, result)
