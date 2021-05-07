extends PanelContainer


onready var network_route_line_edit: = $VBoxContainer/MarginContainer/NetworkRoute/LineEdit


func _ready() -> void:
	var _err = DiscordManager.connect(
		"initialised",
		self, "_on_discord_manager_initialised"
	)


func _on_discord_manager_initialised() -> void:
	DiscordManager.networking.connect(
		"route_update",
		self, "_on_route_update"
	)


func _on_route_update(route: String) -> void:
	network_route_line_edit.text = route
