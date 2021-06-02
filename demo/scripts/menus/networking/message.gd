extends PanelContainer

onready var peer_id_line_edit := $VBoxContainer/MarginContainer/VBoxContainer/PeerID/LineEdit
onready var channel_id_line_edit := $VBoxContainer/MarginContainer/VBoxContainer/ChannelID/LineEdit
onready var data_line_edit := $VBoxContainer/MarginContainer/VBoxContainer/Data/LineEdit


func _ready() -> void:
	var _err = DiscordManager.connect("initialised", self, "_on_discord_manager_initialised")


func _on_discord_manager_initialised() -> void:
	DiscordManager.networking.connect("message", self, "_on_message")


func _on_message(peer_id: int, channel_id: int, data: PoolByteArray) -> void:
	peer_id_line_edit.text = str(peer_id)
	channel_id_line_edit.text = str(channel_id)
	data_line_edit.text = data.get_string_from_utf8()
