extends PanelContainer


onready var code_editor: = $VBoxContainer/MarginContainer/VBoxContainer/CodeEditor
onready var error_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/Error/LineEdit

var FilterClass: = GDScript.new()
var filter_object: Object


func _on_button_down() -> void:
	FilterClass.source_code = code_editor.text
	if filter_object:
		filter_object.free()

	var err: = FilterClass.reload()
	error_line_edit.text = DiscordManager.enum_to_string(Main.Error, err)
	if err == OK:
		filter_object = FilterClass.new()
		DiscordManager.relationships.filter(filter_object, "_filter")
