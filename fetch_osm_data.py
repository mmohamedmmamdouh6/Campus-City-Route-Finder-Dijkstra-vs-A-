import osmnx as ox
import json

valid_nodes = set()

def fetch_and_export(place_name, output_path):
    print(f"Fetching graph for: {place_name}")
    G = ox.graph_from_place(place_name, network_type="walk")
    G = G.to_undirected()    

    data = {"nodes": [], "edges": []}
    
    for node_id, node_data in G.nodes(data=True):
        lat = node_data.get("y")
        lng = node_data.get("x")

        if (lat is None) or (lng is None):
            continue

        valid_nodes.add(node_id)
        data["nodes"].append({
            "id": node_id,
            "lat": node_data["y"],
            "lng": node_data["x"]
        })
    
    for u, v, edge_data in G.edges(data=True):
        if (u not in valid_nodes) or (v not in valid_nodes):
            continue # skip edges with invalid nodes
        distance = edge_data.get("length")
        if (distance is None) :
            continue # distance if not available
        data["edges"].append({
            "from": u,
            "to": v,
            "distance": round(distance, 2)
        })

    with open(output_path, "w") as f:
        json.dump(data, f, indent=2)
    
    print(f"Exported {len(data['nodes'])} nodes and {len(data['edges'])} edges")

if __name__ == "__main__":
    fetch_and_export("Cairo University, Cairo, Egypt", "data/graph_data.json")