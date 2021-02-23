extends PanelContainer


onready var start_line_edit: = $VBoxContainer/HBoxContainer/Start/LineEdit
onready var end_line_edit: = $VBoxContainer/HBoxContainer/End/LineEdit

var timestamps: Discord.ActivityTimestamps setget set_timestamps


func set_timestamps(new_timestamps: Discord.ActivityTimestamps) -> void:
	if new_timestamps:
		start_line_edit.text = str(new_timestamps.start)
		end_line_edit.text = str(new_timestamps.end)
