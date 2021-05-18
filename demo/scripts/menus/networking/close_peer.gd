extends PanelContainer


onready var peer_id_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/PeerID
onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit


func _on_close_button_down() -> void:
	var peer_id: = int(peer_id_line_edit.text)

	var result: int = DiscordManager.networking.close_peer(peer_id)

	result_line_edit.text = DiscordManager.enum_to_string(Discord.Result, result)
