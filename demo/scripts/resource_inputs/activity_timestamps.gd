extends PanelContainer


onready var start_line_edit: = $VBoxContainer/HBoxContainer/Start
onready var end_line_edit: = $VBoxContainer/HBoxContainer/End


func get_timestamps() -> Discord.ActivityTimestamps:
	var timestamps: = Discord.ActivityTimestamps.new()
	timestamps.start = int(start_line_edit.text)
	timestamps.end = int(end_line_edit.text)
	return timestamps
