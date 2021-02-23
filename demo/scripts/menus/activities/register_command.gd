extends PanelContainer


onready var command_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/Command
onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit


func _on_button_down() -> void:
	var command: String = command_line_edit.text

	var result: int = DiscordManager.activities.register_command(command)

	result_line_edit.text = DiscordManager.enum_to_string(
		Discord.Result,
		result
	)
