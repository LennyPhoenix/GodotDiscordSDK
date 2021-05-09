extends PanelContainer


onready var peer_id_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/PeerID
onready var channel_id_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/ChannelID
onready var reliable_check_box: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/Reliable/CheckBox
onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit


func _on_open_button_down() -> void:
	var peer_id: = int(peer_id_line_edit.text)
	var channel_id: = int(channel_id_line_edit.text)
	var reliable: bool = reliable_check_box.pressed

	var result: int = DiscordManager.networking.open_channel(peer_id, channel_id, reliable)

	result_line_edit.text = DiscordManager.enum_to_string(Discord.Result, result)
