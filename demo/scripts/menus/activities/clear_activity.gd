extends PanelContainer


onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit


func _on_button_down() -> void:
	DiscordManager.activities.clear_activity()
	var result: int = yield(DiscordManager.activities, "clear_activity_callback")

	result_line_edit.text = DiscordManager.enum_to_string(
		Discord.Result,
		result
	)
