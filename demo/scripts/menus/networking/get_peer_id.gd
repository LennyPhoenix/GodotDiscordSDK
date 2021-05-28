extends PanelContainer

onready var id_line_edit := $VBoxContainer/MarginContainer/VBoxContainer/ID/LineEdit


func _on_get_peer_id_button_down() -> void:
	var id: int = DiscordManager.networking.get_peer_id()
	id_line_edit.text = str(id)
