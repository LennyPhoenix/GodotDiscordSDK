extends PanelContainer


onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit
onready var count_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Count/LineEdit


func _on_button_down() -> void:
	DiscordManager.relationships.count()
	var ret: Array = yield(DiscordManager.relationships, "count_callback")
	var result: int = ret[0]
	var count: int = ret[1]

	result_line_edit.text = DiscordManager.enum_to_string(Discord.Result, result)
	count_line_edit.text = str(count)
