extends PanelContainer


onready var steam_id_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/SteamID
onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit


func _on_button_down() -> void:
	var steam_id: String = steam_id_line_edit.text

	var result: int = DiscordManager.activities.register_steam(int(steam_id))

	result_line_edit.text = DiscordManager.enum_to_string(
		Discord.Result,
		result
	)
