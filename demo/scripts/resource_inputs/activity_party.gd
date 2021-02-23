extends PanelContainer


onready var id_line_edit: = $VBoxContainer/ID
onready var party_size: = $VBoxContainer/Size


func get_party() -> Discord.ActivityParty:
	var party: = Discord.ActivityParty.new()
	party.id = id_line_edit.text
	party.size = party_size.get_party_size()
	return party
