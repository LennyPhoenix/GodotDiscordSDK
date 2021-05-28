extends PanelContainer

onready var peer_id_line_edit := $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/PeerID
onready var route_line_edit := $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/Route
onready var result_line_edit := $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit


func _on_update_button_down() -> void:
	var peer_id := int(peer_id_line_edit.text)
	var route: String = route_line_edit.text

	var result: int = DiscordManager.networking.update_peer(peer_id, route)

	result_line_edit.text = DiscordManager.enum_to_string(Discord.Result, result)
